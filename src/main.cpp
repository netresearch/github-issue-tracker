#include <optional>

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>

#include "config.h"
#include "network.h"
#include "message.h"
#include "display.h"
#include "ota.h"
#include "fetch.h"

void setup()
{
    // Wire.begin(D5, D6);

    // Init serial
    Serial.begin(115200);
    while (!Serial)
        continue;
    delay(2000);

    // Logo
    Message::logo();
    // setupFetch();
    Fetch::setup();
    Display::setup();
    Network::setup();
    Ota::setup();
}

void loop()
{
    if (Network::loop())
    {
        Ota::loop();
        Fetch::loop();
    }

    // std::optional<int> totalOpenIssues = fetchTotalOpenIssues();
    std::optional<int> totalOpenIssues = 15;
    if (totalOpenIssues)
    {
        // Serial.printf("Total open issues: %d\n", totalOpenIssues.value());
        // Serial.printf("Total open issues: %d\n", totalOpenIssues);
        /*
        display.clearDisplay();
        display.setCursor(0, 0);
        display.printf("%d", totalOpenIssues.value());
        display.display();
        */
    }
    else
    {
        // Serial.println(F("Failed to fetch repositories"));
    }
}
