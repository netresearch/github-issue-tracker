#include <optional>

#include <WiFiClientSecureBearSSL.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>

#include "config.h"

Adafruit_SSD1306 display(128, 32, &Wire, -1);

std::optional<int> fetchTotalOpenIssues();

void setup()
{
    Wire.begin(D5, D6);

    Serial.begin(115200);
    Serial.println();
    Serial.println();

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("Start of SSD1306 failed"));
        for (;;)
        {
        }
    }
    display.display();

    WiFi.begin(SSID, PASSWORD);
    Serial.print(F("Connecting to WiFi ..."));

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(F("."));
    }

    Serial.println(F("Connected to WiFi network"));

    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.clearDisplay();
    display.display();
}

void loop()
{
    delay(10000);

    std::optional<int> totalOpenIssues = fetchTotalOpenIssues();
    if (totalOpenIssues)
    {
        Serial.printf("Total open issues: %d\n", totalOpenIssues.value());

        display.clearDisplay();
        display.setCursor(0, 0);
        display.printf("%d", totalOpenIssues.value());
        display.display();

        // Go to deep sleep for one hour
        // ESP.deepSleep(1000 * 1000 * 60 * 60);
    }
    else
    {
        Serial.println(F("Failed to fetch repositories"));
    }
}

std::optional<int> fetchTotalOpenIssues()
{
    int totalOpenIssues = 0;

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;

    if (!https.begin(client, "https://api.github.com/graphql"))
    {
        Serial.printf("HTTPClient failure\n");

        display.setCursor(0, 0);
        display.print("HTTPClient failure");

        https.end();
        return std::nullopt;
    }

    https.addHeader("Content-Type", "application/json");
    https.addHeader("Authorization", "Bearer " + String(GITHUB_TOKEN));

    int code = https.POST("{\"query\":\"{ organization(login: \\\"netresearch\\\") { repositories(first: 100) { nodes { issues(states: OPEN ) { totalCount } } } } }\"}");

    if (code != 200)
    {
        Serial.printf("HTTPClient failure: %s\n", https.errorToString(code).c_str());

        https.end();
        return std::nullopt;
    }

    DynamicJsonDocument doc(8192);
    DeserializationError error = deserializeJson(doc, https.getStream());
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());

        return std::nullopt;
    }

    https.end();

    for (JsonObject repository : doc["data"]["organization"]["repositories"]["nodes"].as<JsonArray>())
    {
        int openIssues = repository["issues"]["totalCount"];

        totalOpenIssues += openIssues;
    }

    return totalOpenIssues;
}
