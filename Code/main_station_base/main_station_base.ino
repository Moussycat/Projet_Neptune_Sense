#include <WiFi.h>
#include <esp_wifi.h>
#include "time.h"
#include "sntp.h"
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>
#include "WiFiClientSecure.h"
//#include "WiFiClient.h"
#include <PubSubClient.h>

//config
#include "config.h"
//wifi credential
#include "credential.h"
//time
#include "master_time.h"
//Screen
TFT_eSPI tft = TFT_eSPI();
//weather
#include "weather.h"
//butmap
#include "bitmaps.h"
//JSON
#include <Arduino_JSON.h>

WiFiClientSecure wifiClient;
//WiFiClient wifiClient;
PubSubClient mqttClient;
#define TOPIC_NAME "XXXXXXX"

#define PORT  XXXX
#define SIZE_BUFFER 2048
#define TOPIC_HUMIDITY "H_air"
#define TOPIC_PH "PH"
#define TOPIC_AIR "T_air"
#define TOPIC_EAU "T_eau"
#define TOPIC_TDS "TDS"

String H_air;
String PH;
String t_air;
String t_eau;
String tds;


//Save the last Time we pass the boucle
typedef struct{
  int second;
  int min;
  int hour;
  int day;
  int month;
}T;

// Update the last time recorded
void updateLastTime(T* lt,TimeM* t){
  lt->second = t->second;
  lt->min = t->min;
  lt->hour = t->hour;
  lt->day = t->day;
  lt->month = t->month;
}

#define BACKGROUND_COLOR TFT_WHITE
#define TEXT_COLOR TFT_BLACK

//Init object
TimeM timeM;
Weather weather;

// Prototypes for the scheduler functions
void each_5seconds(bool* refresh);
void each_30seconds(bool* refresh);
void each_mins(bool* refresh);
void each_hours(bool* refresh);
void each_days(bool* refresh);

const uint8_t MACAddress[] PROGMEM= {0xAC, 0x67, 0xB2, 0x2B, 0x7F, 0x20};

// Callback function for MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  // Convert the payload to a string
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';

  // Print the received topic and message
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  // Parser le JSON
  JSONVar myObject = JSON.parse(message);

  // Check if parsing was successful
  if (JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing JSON failed!");
      return;
  }

  // Access the "uplink_message" and "decoded_payload" sub-objects
  if (myObject.hasOwnProperty("uplink_message") && 
      myObject["uplink_message"].hasOwnProperty("decoded_payload")) {
      JSONVar decodedPayload = myObject["uplink_message"]["decoded_payload"];

      // Check for the presence of TOPIC_HUMIDITY
      if (decodedPayload.hasOwnProperty(TOPIC_HUMIDITY)) {
          H_air = (const char*)decodedPayload[TOPIC_HUMIDITY];
          Serial.print("Humidity: ");
          Serial.println(H_air);
      } 
      // Check for the presence of TOPIC_PH
      if (decodedPayload.hasOwnProperty(TOPIC_PH)) {
          PH = (const char*)decodedPayload[TOPIC_PH];
          Serial.print("PH: ");
          Serial.println(PH);
      }
      // Check for the presence of TOPIC_AIR
      if (decodedPayload.hasOwnProperty(TOPIC_AIR)) {
          t_air = (const char*)decodedPayload[TOPIC_AIR];
          Serial.print("t_air: ");
          Serial.println(t_air);
      }
      // Check for the presence of TOPIC_EAU
      if (decodedPayload.hasOwnProperty(TOPIC_EAU)) {
          t_eau = (const char*)decodedPayload[TOPIC_EAU];
          Serial.print("t_eau: ");
          Serial.println(t_eau);
      }
      // Check for the presence of TOPIC_TDS
      if (decodedPayload.hasOwnProperty(TOPIC_TDS)) {
          tds = (const char*)decodedPayload[TOPIC_TDS];
          Serial.print("tds: ");
          Serial.println(tds);
      }
  } else {
        Serial.println("decoded_payload not found in uplink_message.");
    }
}

// Reconnect to MQTT server
void reconnect(){
  if(!mqttClient.connected()){
    Serial.println("Connecting to MQTT...");
    mqttClient.connect("esp32_Neptune_Sense",USER_MQTT,PASS_MQTT);
    while (!mqttClient.connected()){
      Serial.print("Failed to connect to MQTT server, code: ");
      Serial.println(mqttClient.state());
      delay(1000);
    }
  Serial.println("Connected to MQTT server");
  }
}

void setup()
{
  SPI.setFrequency(5000000);
  //Set a fix mac adress
  esp_wifi_set_mac(WIFI_IF_STA, &MACAddress[0]);

  #if DEV
    Serial.begin(BAUDRATE);
    Serial.println("Starting setup...");

    //connect to WiFi
    Serial.print("ESP Board MAC Address:  ");
    Serial.println(WiFi.macAddress());
  #endif
  
  //Connect to wifi
  int attempt = 0;
  int cred = 0;
  int nb_credentials = sizeof(credentials)/sizeof(Credential);
  #if DEV
    Serial.printf("\nYou have : %d credentials to test.", nb_credentials);
  #endif
  
  WiFi.mode(WIFI_STA);

  do {
      if (!(attempt%10)){
        WiFi.begin(credentials[cred].ssid, (credentials[cred].password=="")?NULL:credentials[cred].password);
        #if DEV
          Serial.printf("\nConnecting to %s ", credentials[cred].ssid);
        #endif
        cred = (cred<nb_credentials-1)? cred+1:0 ;
      }
      delay(1000);
      attempt++;
      #if DEV
        Serial.print(".");
      #endif
  } while (WiFi.status() != WL_CONNECTED);
  
  #if DEV
    Serial.println(" CONNECTED");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  #endif

  //Set wifi to use ssl certificate
  wifiClient.setInsecure();
  //Connect mqtt
  mqttClient.setClient(wifiClient);
  mqttClient.setServer(SERVER_MQTT, PORT);
  Serial.println("Set callback init");
  mqttClient.setCallback(callback);
  Serial.println("end callback init"); 
  mqttClient.setBufferSize(SIZE_BUFFER);
  reconnect();
  mqttClient.subscribe(TOPIC_NAME);  // Subscribe to the topic 
  

  //init servicies
  tft.init();
  tft.fillScreen(BACKGROUND_COLOR);
  weather.init();
  
  //init time
  int i = 1;
  timeM.init();
  while(!timeM.update_time()){
    #if DEV
    Serial.println("Initilizing time, attempt "+String(i));
    #endif
    i++;
    delay(500);
  }

  init_main();
  #if DEV
    Serial.println("Setup done");
  #endif
}

void loop()
{
  reconnect();
  mqttClient.loop();
  static T lastT = {-1,-1,-1,-1,-1};
  static bool need_refresh = false;

  //update time
  timeM.update_time();

  //Each 30s : 
  if ((timeM.second>=30 && lastT.second<30)||(timeM.second<30 && lastT.second>=30)||(lastT.second==-1)){
    //each minutes
    if(lastT.min != timeM.min){
      //each hours
      if(lastT.hour != timeM.hour){
        //each days
        if(lastT.day != timeM.day){
          each_days(&need_refresh);
        }
        each_hours(&need_refresh);
      }
      each_mins(&need_refresh);
    }
    each_30seconds(&need_refresh);
  }

  //Apply the changes if needed
  if (need_refresh){
    //apply the buffer onto the screen
    
    need_refresh = false;
  }
  
  //update the lastT
  updateLastTime(&lastT,&timeM);

  #if DEV
  //SIMPLE PROCESSOR DELAY (suitable for debug)
  delay(PRECISON_CLOCK);
  #else
  //ESP LIGHT SLEEP MODE (suitable for production)
  //(Slow down the Serial connection and make debug harder)
  esp_sleep_enable_timer_wakeup((PRECISON_CLOCK-100) * 1000);
  esp_light_sleep_start();
  //safe wake-up
  delay(100);
  #endif
}

static void init_main(void){
  static bool need_refresh = false;
  each_days(&need_refresh);
  each_hours(&need_refresh);
  each_mins(&need_refresh);
  each_30seconds(&need_refresh);
  if (need_refresh){
    //apply the buffer onto the screen
    tft.fillScreen(BACKGROUND_COLOR);
    tft.setCursor(120, 0, 2);
    tft.setTextColor(TEXT_COLOR);  
    tft.setTextSize(1);
    tft.println(timeM.hour);
    tft.setCursor(140, 0, 2);
    tft.setTextColor(TEXT_COLOR);  
    tft.setTextSize(1);
    tft.println(":");
    tft.setCursor(150, 0, 2);
    tft.setTextSize(1);
    tft.println(timeM.min);
    //data from outdoor station
    tft.setCursor(2, 20, 2);
    tft.setTextColor(TEXT_COLOR);  
    tft.setTextSize(1);
    tft.println("Température air: ");
    tft.setCursor(2, 40, 2);
    tft.setTextColor(TEXT_COLOR);  
    tft.setTextSize(1);
    tft.println("Température eau: ");
    tft.setCursor(2, 60, 2);
    tft.setTextColor(TEXT_COLOR);  
    tft.setTextSize(1);
    tft.println("PH: ");
    tft.setCursor(2, 80, 2);
    tft.setTextColor(TEXT_COLOR);  
    tft.setTextSize(1);
    tft.println("Humidite: ");
    tft.setCursor(2, 100, 2);
    tft.setTextColor(TEXT_COLOR);  
    tft.setTextSize(1);
    tft.println("TDS: ");

    need_refresh = false;
  }
}

/*======== SCHEDULER =========
*
*  Each function is called at a precise time
*  Here to help code reading
*/
void each_30seconds(bool* refresh){
  #if DEV
    Serial.println("--- 30 SECONDE ---");
  #endif
  //display the time
  tft.fillScreen(BACKGROUND_COLOR);
  // Date
  tft.setCursor(0, 0, 2);
  tft.setTextColor(TEXT_COLOR);  
  tft.setTextSize(1);
  tft.println(timeM.day);
  tft.setCursor(30,0,2);
  tft.setTextSize(1);
  tft.println(timeM.month);
  tft.setCursor(60,0,2);
  tft.setTextSize(1);
  tft.println(timeM.year);
  // Clock
  tft.setCursor(120, 0, 2);
  tft.setTextColor(TEXT_COLOR);  
  tft.setTextSize(1);
  tft.println(timeM.hour);
  tft.setCursor(140, 0, 2);
  tft.setTextColor(TEXT_COLOR);  
  tft.setTextSize(1);
  tft.println(":");
  tft.setCursor(150,0,2);
  tft.setTextColor(TEXT_COLOR);
  tft.setTextSize(1);
  tft.println(timeM.min);
  //weather
  tft.setCursor(60,150,4);
  tft.setTextSize(1);
  tft.println(weather.city);
  tft.setCursor(150,150,4);
  tft.println(weather.temp);
  tft.setCursor(180, 150, 4);
  tft.println(" C");
  tft.drawBitmap( 84, 204,weather_icon[weather.sky], 80, 80, TEXT_COLOR);
  //data from outdoor station
  tft.setCursor(2, 20, 2);
  tft.setTextColor(TEXT_COLOR);  
  tft.setTextSize(1);
  tft.println("Température air: ");
  tft.setCursor(100, 20, 2);
  tft.print(t_air);
  tft.print("   °C");
  tft.setCursor(2, 40, 2);
  tft.setTextColor(TEXT_COLOR);  
  tft.setTextSize(1);
  tft.println("Température eau: ");
  tft.setCursor(100, 40, 2);
  tft.print(t_eau);
  tft.print("   °C");
  tft.setCursor(2, 60, 2);
  tft.setTextColor(TEXT_COLOR);  
  tft.setTextSize(1);
  tft.println("PH: ");
  tft.setCursor(30, 60, 2);
  tft.print(PH);
  tft.setCursor(2, 80, 2);
  tft.setTextColor(TEXT_COLOR);  
  tft.setTextSize(1);
  tft.println("Humidite: ");
  tft.setCursor(60, 80, 2);
  tft.print(t_air);
  tft.print("   %");
  tft.setCursor(2, 100, 2);
  tft.setTextColor(TEXT_COLOR);  
  tft.setTextSize(1);
  tft.println("TDS: ");
  tft.setCursor(40, 100, 2);
  tft.print(t_air);
  tft.print("   ppm");
}
void each_mins(bool* refresh){
  #if DEV
    Serial.println("--- MINS ---");
  #endif
}
void each_hours(bool* refresh){
  #if DEV
    Serial.println("--- HOURS ---");
  #endif
  //clear the screen
  tft.fillScreen(BACKGROUND_COLOR);
  //update the weather data
  weather.get_info();
  //need full refresh
  *refresh = true;
}

void each_days(bool* refresh){
  #if DEV
    Serial.println("--- DAYS ---");
  #endif
  //update the daylight
  //daylight.calculate_sunRiseSet(timeM.year,timeM.month,timeM.day,DAYLIGHT_LATITUDE,timeM.daylight_saving);
}
