
#include <Arduino.h>
#include <ArduinoJson.h>
// #include <HTTPClient.h>

// Custom classes and configuration
#include "config.h"
#include "message.h"

int iteration = 0;
int iterationTime = 0;
const int iterationTimeWait = 1000 * 60 * 15; // 15 minutes

std::optional<int> fetchTotalOpenIssues();

class Fetch
{
public:
    static void setup()
    {
        Message::info("Setup: Fetch");
    }

    static int loop(int delayTime)
    {
        iteration++;
        iterationTime = iteration * delayTime;

        // If every 30 seconds have passed
        if (iterationTime % iterationTimeWait == 0)
        {
            // std::optional<int> totalOpenIssues = fetchTotalOpenIssues();
            int totalOpenIssues = iteration;
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
};
/*
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
*/
