#include <optional>

// Libraries
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>

// Function and configuration
#include "globals.h"
#include "config.h"
#include "network.h"
#include "message.h"
#include "display.h"
#include "ota.h"
#include "fetch.h"

// Variables and constants
const int delayTime = 10000;
int G_issueCount = 0;

void setup()
{
    // Init serial
    Serial.begin(115200);
    while (!Serial)
        continue;
    delay(2000);

    // Logo
    Display::setup();
    Message::logo();
    Display::set("Connecting WiFi", true);
    Network::setup();
    Ota::setup();
}

void loop()
{
    if (Network::loop())
    {
        Ota::loop();
        auto issueCount = Fetch::fetchIssues(delayTime);
        if (issueCount.has_value())
        {
            G_issueCount = issueCount.value();
            Message::info("Issue count:\t" + String(G_issueCount));
            Display::set(String(G_issueCount));
        }
        else
        {
            Display::set("Data error", true);
        }

        delay(delayTime);
    }
}
