#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 32, &Wire, -1);

void setupDisplay()
{
    Serial.println("✅  Setup: Display");

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("Start of SSD1306 failed"));
        for (;;)
        {
        }
    }

    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.clearDisplay();
    display.display();

    display.display();
}
