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
        auto issueCount = Fetch::loop(delayTime);
        if (issueCount != -1)
        {
            G_issueCount = issueCount;
            Message::info("Issue count: " + String(G_issueCount.value()));
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
