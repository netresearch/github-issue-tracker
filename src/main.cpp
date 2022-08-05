#include <optional>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>

#include "config.h"

WiFiClient client;
HTTPClient http;

std::optional<String> fetchRawGithubRepositories();

void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println();

    WiFi.begin(SSID, PASSWORD);
    Serial.print(F("Connecting to WiFi ..."));

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(F("."));
    }

    Serial.println(F("Connected to WiFi network"));
}

void loop()
{
    delay(1000);

    int totalIssues = 0;

    std::optional<String> rawRepositories = fetchRawGithubRepositories();
    if (rawRepositories)
    {
        StaticJsonDocument<JSON_ARRAY_SIZE(100)> jsonRepositories;
        DeserializationError error = deserializeJson(jsonRepositories, rawRepositories.value());
        if (error)
        {
            Serial.println(F("Failed to parse JSON"));
            return;
        }

        // JsonArray repositories = jsonRepositories.as<JsonArray>();
        // for (JsonObject repository : repositories)
        // {
        //     const char *name = repository["name"];
        //     int openIssues = repository["open_issues_count"];
        //     Serial.printf("%s: %d\n", name, openIssues);

        //     totalIssues += openIssues;
        // }

        Serial.printf("Total open issues: %d\n", totalIssues);

        // Go to deep sleep for one hour
        // ESP.deepSleep(1000 * 1000 * 60 * 60);
    }
    else
    {
        Serial.println(F("Failed to fetch repositories"));
    }
}

std::optional<String> fetchRawGithubRepositories()
{
    if (!http.begin(client, "https://api.github.com/orgs/netresearch/repos"))
    {
        Serial.println("HTTPClient failure");
        http.end();
        return std::nullopt;
    }

    int code = http.GET();
    if (code != 200)
    {
        Serial.printf("HTTPClient failure: %d\n", code);
        http.end();
        return std::nullopt;
    }

    String payload = http.getString();

    http.end();

    return payload;
}
