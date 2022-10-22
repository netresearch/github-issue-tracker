#include <Adafruit_SSD1306.h>
#include <Arduino.h>

// Configuration
#include "config.h"

// Custom classes
#include "message.h"

Adafruit_SSD1306 display(128, 32, &Wire, -1);

class Display
{
public:
    static void setup()
    {
        Message::info("Setup: Display");
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        display.setTextSize(3);
        display.setTextColor(SSD1306_WHITE);
        display.clearDisplay();
        display.display();
    }

    static void set(String text)
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print(text);
        display.display();
    }
};
