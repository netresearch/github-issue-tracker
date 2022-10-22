/*
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
*/
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include "config.h"
#include "message.h"

class Network
{
public:
    static void setup()
    {
        Message::info("Setup: Network");
        String payload = "";

        WiFi.begin(WIFI_SSID_1, WIFI_PASSWORD_1);
        Message::working("Connecting to WiFi ...", false);
        delay(1000);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.print(F("."));
        }

        Message::br();
        Message::success("Connected to WiFi network.\n");
        /*

        WiFiMulti wifiMulti;
        wifiMulti.addAP(WIFI_SSID_1, WIFI_PASSWORD_1);
        wifiMulti.addAP(WIFI_SSID_2, WIFI_PASSWORD_2);
        wifiMulti.addAP(WIFI_SSID_3, WIFI_PASSWORD_3);
        wifiMulti.addAP(WIFI_SSID_4, WIFI_PASSWORD_4);

        Serial.println(F("\n🤖  Connecting to WiFi …"));
        if (wifiMulti.run() == WL_CONNECTED)
        {
            Serial.println("🤖  Connected to WiFi network!");
            Serial.println("\tSSID:\t\t" + WiFi.SSID());
            Serial.println("\tIP address:\t" + WiFi.localIP().toString());
            Serial.println("\tGateway:\t" + WiFi.gatewayIP().toString());
            Serial.println("\tSubnet mask:\t" + WiFi.subnetMask().toString());
            Serial.println("\tDNS:\t\t" + WiFi.dnsIP().toString());
            Serial.println("\tMAC address:\t" + WiFi.macAddress());

            // Request
            HTTPClient http;

            // Make the request
            http.begin(API_URL_APPOINTMENTS);
            int httpCode = http.GET();

            if (httpCode == 200)
            {
                // Get the response payload
                payload = http.getString();
            }
            else
            {
                Serial.printf("\n❌  [HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }

            // Free the resources
            http.end();
        }
        else
        {
            Serial.println(F("❌  Failed to connect to WiFi network."));
        }
    */
    };
};
