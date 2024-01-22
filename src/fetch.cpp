
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClient.h>
#include <optional>

// Custom classes and configuration
#include "config.h"
#include "message.h"

// Global variables
#include "globals.h"

namespace Fetch
{
    // Constants
    const int iterationTimeWait = 1000 * 60 * 15; // 15 minutes
    // const int iterationTimeWait = 1000 * 10; // 10 seconds

    // Variables
    int iteration = 0;
    int iterationFirst = true;
    int iterationTime = 0;
    std::optional<int> fetchTotalOpenIssues();

    /**
     * @brief Setup the fetch class
     * @return void
     */
    void setup()
    {
        Message::info("Setup: Fetch");
    }

    /**
     * @brief Fetches the total number of open issues from the GitHub API
     * @param delayTime Time to wait each iteration
     * @return std::optional<int> Total issue count
     */
    std::optional<int> loop(int delayTime)
    {
        // @todo Bring iteration loop to main loop
        iteration++;
        iterationTime = iteration * delayTime;

        // If every 30 seconds have passed or if it's the first iteration
        if (iterationTime % iterationTimeWait == 0 || iterationFirst)
        {
            iterationFirst = false;
            std::optional<int> totalOpenIssues = fetchTotalOpenIssues();
            G_issueCount = totalOpenIssues;
            iteration = 0;
        }
        return G_issueCount;
    }

    /**
     * @brief Fetches the total number of open issues from the GitHub API
     *
     * @return std::optional<int> Total issue count
     */
    std::optional<int> fetchTotalOpenIssues()
    {
        int totalOpenIssues = -1;

        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient https;

        Message::working("Fetch data from GitHub API\t", false);

        if (!https.begin(client, "https://api.github.com/graphql"))
        {
            Message::error("Unable to connect to GitHub API");
            https.end();
            return std::nullopt;
        }

        https.addHeader("Content-Type", "application/json");
        https.addHeader("Authorization", "Bearer " + String(GITHUB_TOKEN));

        // POST request with query
        int httpCode = https.POST("{\"query\":\"{ search(query: \\\"org:" + String(GITHUB_ORGANIZATION) + " state:open\\\", type: ISSUE) { issueCount}}\"}");
        // int httpCode = https.POST("{\"query\":\"{ organization(login: \\\"netresearch\\\") { repositories(first: 100) { nodes { issues(states: OPEN ) { totalCount } } } } }\"}");
        if (httpCode != 200)
        {
            Message::error("Unable to fetch data from GitHub API");
            Serial.printf("\tHTTPClient failure: ");
            Serial.println(httpCode);
            while (client.available())
            {
                char c = client.read();
                Serial.println(c);
            }

            https.end();
            return std::nullopt;
        } else {
            Message::success("Fetch data from GitHub API successfull", true, true);
            DynamicJsonDocument doc(8192);
            DeserializationError error = deserializeJson(doc, https.getStream());

            if (error)
            {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
                return std::nullopt;
            }
            totalOpenIssues = doc["data"]["search"]["issueCount"];
            https.end();
        }
        return totalOpenIssues;
    }
};
