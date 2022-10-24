#include <ESP8266WiFiMulti.h>
// #include <HTTPClient.h>

// Custom classes and configuration
#include "config.h"
#include "message.h"

// Instances
ESP8266WiFiMulti wifiMulti;

// Configuration
uint8_t networkTrys = 0;
bool networkConnected = false;
const uint32_t networkConnectTimeoutMs = 5000; // WiFi connect timeout per AP. Increase when connecting takes longer.

// Namespace
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
                Message::success("Connected to WiFi network", true, true);
                Message::data("MAC:\t\t" + WiFi.macAddress());
                Message::data("SSID:\t\t" + WiFi.SSID());
                Message::data("IP:\t\t" + WiFi.localIP().toString());
                Message::data("DNS:\t\t" + WiFi.dnsIP().toString());
                Message::data("Gateway:\t" + WiFi.gatewayIP().toString());
                Message::data("Subnet:\t" + WiFi.subnetMask().toString());
                Message::data("RSSI:\t\t" + String(WiFi.RSSI()) + " dBm");
                Message::data("Channel:\t" + String(WiFi.channel()));

                networkConnected = true;
            }
        }
    }
};
