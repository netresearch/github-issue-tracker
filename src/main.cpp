#include <optional>

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>

// Custom classes and configuration
#include "config.h"
#include "network.h"
#include "message.h"
#include "display.h"
#include "ota.h"
#include "fetch.h"

// Variables and constants
const int delayTime = 10000;
std::optional<int> issueCount = 0;

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
        issueCount = Fetch::loop(delayTime);
        if (issueCount != -1)
        {
            Message::info("Issue count: " + String(issueCount.value()));
            // Display::set(String(issueCount.value()));
        }

        delay(delayTime);
    }

    /*
   std::optional<int> totalOpenIssues = fetchTotalOpenIssues();
    if (totalOpenIssues)
    {
        // Serial.printf("Total open issues: %d\n", totalOpenIssues.value());
        // Serial.printf("Total open issues: %d\n", totalOpenIssues);
        display.clearDisplay();
        display.setCursor(0, 0);
        display.printf("%d", totalOpenIssues.value());
        display.display();
    }
    else
    {
        // Serial.println(F("Failed to fetch repositories"));
    }
    */
}
