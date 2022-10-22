#include <Arduino.h>
#include <ArduinoOTA.h>

// Configuration
#include "config.h"

// Custom classes
#include "message.h"

class Ota
{

public:
    static void setup()
    {
        // Hostname defaults to esp8266-[ChipID]
        ArduinoOTA.setHostname(OTA_HOSTNAME);

        // No authentication by default
        ArduinoOTA.setPassword((const char *)OTA_PASSWORD);

        ArduinoOTA.onStart([]()
                           {
            Message::logo();
            Message::working("OTA Update started"); });
        ArduinoOTA.onEnd([]()
                         { Message::success("OTA Update finished"); });
        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                              { Message::working("Progress: " + String(progress / (total / 100)) + "%"); });
        ArduinoOTA.begin();
    }

    static void loop()
    {
        ArduinoOTA.handle();
    }
};
