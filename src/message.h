#pragma once
#include <Arduino.h>

// Class to serial print messages
class Message
{

public:
    static void overwrite(bool clearLine = true)
    {
        if (clearLine)
        {
            Serial.print("\r");
            for (int i = 0; i < 80; i++)
                Serial.print(" ");
        }
        Serial.print("\r");
    }

    static void logo()
    {
        Serial.println("");
        Serial.println(" __     __");
        Serial.println("| _| __|_ |");
        Serial.println("| | '_ \\| |");
        Serial.println("| | | | | |");
        Serial.println("| |_| |_| |");
        Serial.println("|__|   |__|");
        Serial.println("");
    }

    static void logoBold()
    {
        Serial.println("");
        Serial.println("#####        #####");
        Serial.println("#     #    #     #");
        Serial.println("#     ##   #     #");
        Serial.println("#     # #  #     #");
        Serial.println("#     #  # #     #");
        Serial.println("#     #   ##     #");
        Serial.println("##### #    # #####");
        Serial.println("");
    }

    static void br()
    {
        Serial.println("");
    }

    static void info(String message, bool newline = true, bool overwrite = false)
    {
        if (overwrite)
            Message::overwrite();
        if (newline)
            Serial.println("ℹ️\t" + message);
        else
            Serial.print("ℹ️\t" + message);
    }

    static void working(String message, bool newline = true)
    {
        if (newline)
            Serial.println("🤖\t" + message);
        else
            Serial.print("🤖\t" + message);
    }

    static void success(String message, bool newline = true, bool overwrite = false)
    {
        if (overwrite)
            Message::overwrite();
        if (newline)
            Serial.println("✅\t" + message);
        else
            Serial.print("✅\t" + message);
    }

    static void warning(String message)
    {
        Serial.println("⚠️\t" + message);
    }

    static void error(String message)
    {
        Serial.println("🚩\t" + message);
    }
};
