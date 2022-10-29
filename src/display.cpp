#include <Arduino.h>
#include <Adafruit_SSD1306.h>

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
    void set(String text)
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print(text);
        display.display();
    }
}
