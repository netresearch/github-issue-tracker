#include <Arduino.h>

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    for (int i = 10; i <= 200; i=i+10)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(i);
        digitalWrite(LED_BUILTIN, LOW);
        delay(i);
    }
}
