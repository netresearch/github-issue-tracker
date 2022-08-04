#include <Arduino.h>

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    for (int i = 50; i < 1000; i=i+10)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(i);
        digitalWrite(LED_BUILTIN, LOW);
        delay(i);
    }
}
