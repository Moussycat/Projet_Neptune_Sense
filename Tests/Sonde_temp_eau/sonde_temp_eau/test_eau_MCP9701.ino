// the setup routine runs once when you press reset:
#define EAUPIN PB1

float voltage1 =0;
int samples1 =20;

float eau (float voltage) {
    return ((voltage*22.6)/250);
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
    int measurings=0;

    for (int i = 0; i < samples1; i++)
    {
        measurings += analogRead(EAUPIN);
        delay(10);

    }

    float voltage1 = measurings/samples1;
    Serial.print(eau(voltage1));
    Serial.println("°C");
    delay(1000);
}