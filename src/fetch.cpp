
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <optional>

// Custom classes and configuration
#include "config.h"
#include "message.h"
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

    /**
     * @brief Fetches the total number of open issues from the GitHub API
     *
     * @return std::optional<int> Total issue count
     */
    std::optional<int> fetchTotalOpenIssues()
    {
        int totalOpenIssues = 0;

        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient https;

        if (!https.begin(client, "https://api.github.com/graphql"))
        {
            Message::error("Unable to connect to GitHub API");
            https.end();
            return std::nullopt;
        }

        G_issueCount = 0;

        https.addHeader("Content-Type", "application/json");
        https.addHeader("Authorization", "Bearer " + String(GITHUB_TOKEN));

        // POST request with query
        // String query = "{\"query\":\"{ search(query: \"org:"+ String(GITHUB_OWNER) + " state:open\", type: ISSUE) { issueCount  }}\",\"variables\":{}}";
        int httpCode = https.POST("{\"query\":\"{ search(query: \"org:" + String(GITHUB_ORGANISATION) + " state:open\", type: ISSUE) { issueCount  }}\",\"variables\":{}}");

        if (httpCode != 200)
        {
            Message::error("Unable to fetch data from GitHub API");
            Serial.printf("\t\tHTTPClient failure: %s\n", https.errorToString(httpCode).c_str());

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
