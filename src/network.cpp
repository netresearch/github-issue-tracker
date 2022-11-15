// Libraries
#include <ESP8266WiFiMulti.h>

#include "network.h"

// Custom classes and configuration
#include "config.h"
#include "message.h"

// Global variables
#include "globals.h"

namespace Network
{
    // Configuration
    uint8_t networkTrys = 0;
    bool networkConnected = false;
    // WiFi connect timeout per AP. Increase when connecting takes longer.
    const uint32_t networkConnectTimeoutMs = 5000;

    // Namespace
    using namespace std;

    void setup()
    {
        Message::info("Setup: Network");
        String payload = "";

        // Don't save WiFi configuration in flash
        WiFi.persistent(false);

        // Set WiFi to station mode
        WiFi.mode(WIFI_STA);

        // Register multi WiFi networks
        G_wifiMulti.addAP(WIFI_SSID_1, WIFI_PASSWORD_1);
        G_wifiMulti.addAP(WIFI_SSID_2, WIFI_PASSWORD_2);
        G_wifiMulti.addAP(WIFI_SSID_3, WIFI_PASSWORD_3);
        G_wifiMulti.addAP(WIFI_SSID_4, WIFI_PASSWORD_4);

        Message::working("Connecting to WiFi\t", false);

    }

    bool loop()
    {
        if (G_wifiMulti.run(networkConnectTimeoutMs) != WL_CONNECTED)
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
            return false;
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
            return true;
        }
    }
}
