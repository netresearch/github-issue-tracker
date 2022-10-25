
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <optional>

// Custom classes and configuration
#include "config.h"
#include "message.h"

// Constants
const int iterationTimeWait = 1000 * 60 * 15; // 15 minutes
// const int iterationTimeWait = 1000 * 10; // 10 seconds

// Variables
int iteration = 0;
int iterationFirst = true;
int iterationTime = 0;

std::optional<int> fetchTotalOpenIssues();

class Fetch
{
public:
    /**
     * @brief Setup the fetch class
     * @return void
     */
    static void setup()
    {
        Message::info("Setup: Fetch");
    }

    /**
     * @brief Fetches the total number of open issues from the GitHub API
     * @param delayTime Time to wait each iteration
     * @return std::optional<int> Total issue count
     */
    static std::optional<int> loop(int delayTime)
    {
        // @todo Bring iteration loop to main loop
        iteration++;
        iterationTime = iteration * delayTime;

        // If every 30 seconds have passed or if it's the first iteration
        if (iterationTime % iterationTimeWait == 0 || iterationFirst)
        {
            iterationFirst = false;
            std::optional<int> totalOpenIssues = fetchTotalOpenIssues();
            if (totalOpenIssues)
            {
                return totalOpenIssues;
            }
            else
            {
                return -1;
            }
            iteration = 0;
        }
        return -1;
    }

private:
    /**
     * @brief Fetches the total number of open issues from the GitHub API
     *
     * @return std::optional<int> Total issue count
     */
    static std::optional<int> fetchTotalOpenIssues()
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
};
