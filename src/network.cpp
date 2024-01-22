// Libraries
#include <ESP8266WiFi.h>

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

    void setup()
    {
        Message::info("Setup: Network");
        String payload = "";

        // Don't save WiFi configuration in flash
        WiFi.persistent(false);

        // Set WiFi to station mode
        WiFi.mode(WIFI_STA);

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        Message::working("Connecting to WiFi\t", false);
    }

    bool loop()
    {
        if (WiFi.status() != WL_CONNECTED)
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
