#include <Arduino.h>

int pHSense = A0;
int samples = 10;
float adc_resolution = 1024.0;

void setup()
{
    Serial.begin(9600);
    delay(100);
    Serial.println("cimpleo temp Sense");
}

float ph (float voltage) {
    return 7 + ((4 - voltage) / 0.18);
}

void loop()
{
    int measurings=0;

    for (int i = 0; i < samples; i++)
    {
        measurings += analogRead(pHSense);
        delay(10);

    }

    float voltage = 5 / adc_resolution * measurings/samples;
    Serial.print("ph= ");
    Serial.println(ph(voltage));
    delay(1000);
}
