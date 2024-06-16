#include <WiFi.h>
#include "esp_wifi.h"
#include <PubSubClient.h>

// WIFI-----------------------------------------------------------------------------------------------------------------------------------------------
#define DEV 1
typedef struct {
  char* ssid;
  char* password; 
}Credential;

const Credential credentials[4]={
  {"iPhone de Louise", "XXXXX"},
  {"Livebox-BC5E", "XXXXX"},
  {"IoT",NULL}
};
const uint8_t MACAdress[] PROGMEM= {0xAC, 0x67, 0x2B, 0xB2, 0x7F, 0x20};


//MQTT broker ---------------------------------------------------------------------------------------------------------------------------------------
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "emqx/esp32";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
    Serial.begin(115200);
    delay(1000);
    //WiFi ---------------------------------------------------------------------------------------------------------------------------------
    #if DEV
      //Set a fix mac adress
      esp_wifi_set_mac(WIFI_IF_STA,&MACAdress[0]);
      //connect to Wifi
      Serial.println("ESP Board MAC Adress: ");
      Serial.println(WiFi.macAddress());
    #endif
    
    int attempt =0;
    int cred =0;
    int nb_credentials = sizeof(credentials)/sizeof(Credential);
    //connect to wifi
    #if DEV
    Serial.printf("\nYou have: %d credentials to test.", nb_credentials);
    #endif

    WiFi.mode(WIFI_STA);

    do {
      if(!(attempt%10)){
        WiFi.begin(credentials[cred].ssid, (credentials[cred].password=="")?NULL:credentials[cred].password);
        #if DEV
        Serial.printf("\nConnecting to %s", credentials[cred].ssid);
        #endif
        cred= (cred<nb_credentials-1)? cred+1:0;
      }
      delay(1000);
      attempt++;
      #if DEV
        Serial.print(".");
      #endif
    }while(WiFi.status() != WL_CONNECTED);

    #if DEV
      Serial.println("CONNECTED");
      Serial.print(" IP address: ");
      Serial.println(WiFi.localIP());
    #endif  

    #if DEV
      Serial.println("Setup done");
    #endif

    //MQTT -----------------------------------------------------------------------------------------------------------------------------------
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public EMQX MQTT broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // Publish and subscribe
    client.publish(topic, "Hi, I'm ESP32 ^^");
    client.subscribe(topic);
}


void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void loop(){
  client.loop();
}