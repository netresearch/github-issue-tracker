#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Configuration
#include "config.h"

// Custom classes
#include "message.h"

Adafruit_SSD1306 display(128, 32, &Wire, -1);

namespace Display
{
    /**
     * @brief Setup the display class
     * @return void
     */
    void setup()
    {
        Message::info("Setup: Display");
        Wire.begin(D5, D6);
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        display.setTextSize(3);
        display.setTextColor(SSD1306_WHITE);
        display.clearDisplay();
        display.display();
        Message::success("Display setup complete");
    }

    /**
     * @brief Displays the total number of open issues
     * @param text String to print on the display
     * @return void
     */
    void set(String text, bool small = false)
    {
        display.clearDisplay();

        if (small)
        {
            display.setTextSize(1);
        }
        else
        {
            display.setTextSize(3);
        }

        display.setCursor(0, 0);
        display.print(text);
        display.display();
    }
}
