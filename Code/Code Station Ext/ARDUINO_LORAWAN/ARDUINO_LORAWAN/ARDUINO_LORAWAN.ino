/* INCLUDE */

#include <STM32LoRaWAN.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include "credential_ext.h"

/* DEFINE */
// Capteur Temp air
#define DHTPIN PA9      // Pin capteur temp air PA_12
#define DHTTYPE DHT11  // Définition du type de capteur temp air

#define PHPIN PB4  // Pin Sonde PH4

#define EAUPIN PA10 //Pin sonde de temperature d'eau

#define BTN_PRESS_PIN 11  // Pin numérique bouton d'envoi instantané de données

#define LED_COM_PIN 5  // Pin numérique pour la LED de communication (BLEU)

#define TdsSensorPin PB2  // Pin analogique sonde TDS
#define VREF 3.3          //  tension de référence analogique (Volt) de l'ADC
#define SCOUNT 30         // somme du nombre de points d'échantillonnage

/* CLASS */
STM32LoRaWAN modem;

/* VARIABLES */
// LoraWan
static const unsigned long TX_INTERVAL = 60000;  // Interval d'envoi en ms
unsigned long last_tx = 0;
DHT dht(DHTPIN, DHTTYPE);  // Intégration de la broche et du type

// Sonde PH
int samples = 10;
float adc_resolution = 1024.0;
String phInfo;

//sonde de température d'eau
String EauInfo;

// Bouton pression (envoi instantané de données)
bool buttonPressed = false;  // Variable pour suivre l'état du bouton

// Sonde TDS
int analogBuffer[SCOUNT];  // stocke la valeur analogique dans le tableau, lue depuis l'ADC
int analogBufferIndex = 0;
float averageVoltage = 0;
float tdsValue = 0;
float temperature = 25;  // température actuelle pour la compensation


/* Get the rtc object */
STM32RTC& rtc = STM32RTC::getInstance();

// permet de compter un nombre de periode de 100 ms
void compteur(int i){
  int a=0;
  while (a<i){
    unsigned long tempsDebut = millis(); // Définir le temps de départ
    while (millis() - tempsDebut < 98) {
      a+=1;
    }
  }
}


void setup() {

  /* Begin */
  Serial.begin(115200);
  Serial.println("Start");

  modem.begin(EU868);  // Config du modem
  dht.begin();         // Config du capteur temp air

  pinMode(BTN_PRESS_PIN, INPUT);  // Config de la broche bouton

  pinMode(LED_COM_PIN, OUTPUT);  // Config de la broche led com
  digitalWrite(LED_COM_PIN, LOW);

  pinMode(TdsSensorPin, INPUT);  // Config Sond TDS

  /* Lora Keys */
  bool connected = modem.joinOTAA(/* AppEui */ APPEUI, /* AppKey */ APPKEY, /* DevEui */ DEVEUI);
  //bool connected = modem.joinABP(/* DevAddr */ "00000000", /* NwkSKey */ "00000000000000000000000000000000", /* AppSKey */ "00000000000000000000000000000000");

  /* Jonction Lora */
  if (connected) {
    Serial.println("Joined");
  } else {
    Serial.println("Join failed");
    while (true) /* infinite loop */
      ;
  }
}

/* FONCTIONS */
// Envoi des données en Lora dans un JSON
void send_packet() {

  //Mesures nécessaires avant création de l'objet JSON
  ph_measure();
  TDS_measure();
  eau_measure();
  // Créer un objet JSON et récupération des données
  StaticJsonDocument<512> doc;
  doc["T_air"] = String(dht.readTemperature());
  doc["H_air"] = String(dht.readHumidity());
  doc["PH"] = phInfo;
  doc["TDS"] = String(tdsValue) + "ppm";
  doc["T_eau"] = EauInfo;


  // Sérialiser l'objet JSON en une chaîne de caractères
  String jsonStr;
  serializeJson(doc, jsonStr);

  // Préparer et envoyer le paquet LoRa
  modem.setPort(10);
  modem.beginPacket();
  modem.write(jsonStr.c_str(), jsonStr.length());
  if (modem.endPacket() == (int)jsonStr.length()) {
    Serial.println("Sent packet: " + jsonStr);

    digitalWrite(LED_COM_PIN, HIGH);  // Allumer la LED après un envoi réussi
    compteur(10);                      // Garder la LED allumée pendant 1 seconde
    digitalWrite(LED_COM_PIN, LOW);   // Éteindre la LED

  } else {
    Serial.println("Failed to send packet");
  }

  // Vérifier les messages downlink
  if (modem.available()) {
    Serial.print("Received packet on port ");
    Serial.print(modem.getDownlinkPort());
    Serial.print(":");
    while (modem.available()) {
      uint8_t b = modem.read();
      Serial.print(" ");
      Serial.print(b >> 4, HEX);
      Serial.print(b & 0xF, HEX);
    }
    Serial.println();
  }
}

float eau (float voltage1) {
    return ((voltage1*22.6)/250);
}
void eau_measure() {
    int measuring=0;

    for (int i = 0; i < samples; i++)
    {
        measuring += analogRead(EAUPIN);
        compteur(1);

    }
    float voltage1 = measuring/samples;
    EauInfo = String(eau(voltage1));
}

// Convertion PH
float ph(float voltage) {
  return 7 + ((2 - voltage) / 0.18);
}

// Mesure PH
void ph_measure() {
  int measurings = 0;
  for (int i = 0; i < samples; i++) {
    measurings += analogRead(PHPIN);
    compteur(1);
  }
  float voltage = 3.3 / adc_resolution * measurings / samples;
  phInfo = String(ph(voltage));
}

// Sonde TDS
int getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  // si la longueur du tableau est impair, retourner la valeur médiane
  if ((iFilterLen & 1) > 0) {
    bTemp = bTab[(iFilterLen - 1) / 2];
  } else {
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  }
  return bTemp;
}

void TDS_measure() {
  for (int i =0;i<SCOUNT;i++){
    analogBuffer[i] = analogRead(TdsSensorPin);    // lire la valeur analogique et la stocker dans le tampon
  }
  // lire la valeur analogique de manière plus stable grâce à l'algorithme de filtrage médian, et la convertir en valeur de tension
  averageVoltage = getMedianNum(analogBuffer, SCOUNT) * (float)VREF / 4096.0;
  // formule de compensation de température : fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
  //temperature compensation
  float compensationVoltage = averageVoltage / compensationCoefficient;
  // convertir la valeur de tension en valeur de TDS
  tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;
}

/* LOOP */
void loop() {
  /* Vérification de l'état du bouton */
  if (digitalRead(BTN_PRESS_PIN) == HIGH) {
    Serial.println("Bouton Pressé");
    send_packet();  // Envoyez les données immédiatement lorsque le bouton est pressé
    Serial.println("Envoi instantané effectué");
    while (digitalRead(BTN_PRESS_PIN) == HIGH)
      ;  // Attendre que le bouton soit relâché pour éviter les envois multiples
  }

  /* Cycle habituel d'envoi de données */
  if (!last_tx || millis() - last_tx > TX_INTERVAL) {
    send_packet();
    last_tx = millis();
  }
}