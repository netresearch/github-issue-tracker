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
std::optional<int> G_issueCount = 0;

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
    Fetch::setup();
    Display::set("Connecting WiFi", true);
    Network::setup();
    Ota::setup();
}

void loop()
{
    if (Network::loop())
    {
        Ota::loop();
        auto issueCount = Fetch::loop(delayTime);
        if (issueCount != -1)
        {
            G_issueCount = issueCount;
            Message::info("Issue count:\t" + String(issueCount.value()));
            Display::set(String(issueCount.value()));
        }
        else
        {
            Message::error("Issue count:\t" + String(issueCount.value()));
            Display::set("Data error", true);
        }

        delay(delayTime);
    }
}
