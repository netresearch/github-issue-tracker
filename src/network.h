/*
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
*/
#include <ESP8266WiFiMulti.h>

#include "config.h"
#include "message.h"

ESP8266WiFiMulti wifiMulti;
uint8_t networkTrys = 0;
bool networkConnected = false;
// WiFi connect timeout per AP. Increase when connecting takes longer.
const uint32_t networkConnectTimeoutMs = 100;

using namespace std;

class Network
{

public:
    static void setup()
    {
        Message::info("Setup: Network");
        String payload = "";

        // Don't save WiFi configuration in flash
        WiFi.persistent(false);

        // Set WiFi to station mode
        WiFi.mode(WIFI_STA);

        // Register multi WiFi networks
        wifiMulti.addAP(WIFI_SSID_1, WIFI_PASSWORD_1);
        wifiMulti.addAP(WIFI_SSID_2, WIFI_PASSWORD_2);
        wifiMulti.addAP(WIFI_SSID_3, WIFI_PASSWORD_3);
        wifiMulti.addAP(WIFI_SSID_4, WIFI_PASSWORD_4);

        Message::working("Connecting to WiFi\t", false);

        /*
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

    static void loop()
    {
        // Iterate over WiFi networks
        if (wifiMulti.run(networkConnectTimeoutMs) != WL_CONNECTED)
        {
            if (networkTrys % 6 == 0)
            {
                Serial.print(F("\r\t\t\t\t      "));
                Serial.print(F("\r\t\t\t\t"));
            }
            else
            {
                Serial.print(F("."));
            }
            networkTrys++;
        }
        else
        {
            if (networkConnected == false)
            {
                // Message::br();
                Message::success("Connected to WiFi network", true, true);
                Message::info(WiFi.localIP().toString());
                Message::info("\tIP:\t" + WiFi.localIP().toString());
                Message::info("\tRSSI:\t" + String(WiFi.RSSI()) + " dBm");
                Message::info("\tChannel:\t" + String(WiFi.channel()));
                /*
                Message::info(F("SSID:\t" + WiFi.SSID()));
                Message::info("MAC:\t" + WiFi.macAddress());
                Message::info("RSSI:\t" + String(WiFi.RSSI()) + " dBm");
                Message::info("Subnet:\t" + WiFi.subnetMask());
                Message::info("Gateway:\t" + WiFi.gatewayIP());
                Message::info("DNS:\t" + WiFi.dnsIP());
                */
                networkConnected = true;
            }
        }
    }
};
