#include <Arduino.h>

namespace Message
{
    /**
     * @brief Prints a message to the serial port
     * @param message String to print
     * @return void
     */
    void overwrite(bool clearLine = true)
    {
        if (clearLine)
        {
            Serial.print("\r");
            for (int i = 0; i < 80; i++)
                Serial.print(" ");
        }
        Serial.print("\r");
    }

    /**
     * @brief Prints the logo to the serial port
     * @return void
     */
    void logo()
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

    /**
     * @brief Prints the bold logo to the serial port
     * @return void
     */
    void logoBold()
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

    /**
     * @brief Prints a line break to the serial port
     * @return void
     */
    void br()
    {
        Serial.println("");
    }

    /**
     * @brief Prints a message to the serial port
     * @param message To display on serial port
     * @param newline Whether to print a newline after the message
     * @param clearLine Whether to clear the line before printing the message
     * @return void
     */
    void info(String message, bool newline = true, bool overwrite = false)
    {
        if (overwrite)
            Message::overwrite();
        if (newline)
            Serial.println("ℹ️\t" + message);
        else
            Serial.print("ℹ️\t" + message);
    }

    /**
     * @brief Prints a message to the serial port
     * @param message String to print
     * @return void
     */
    void data(String message)
    {
        Serial.println("\t♯ " + message);
    }

    /**
     * @brief Prints a message to the serial port
     * @param message String to print on serial port
     * @param newline Whether to print a newline after the message
     * @return void
     */
    void working(String message, bool newline = true)
    {
        if (newline)
            Serial.println("🤖\t" + message);
        else
            Serial.print("🤖\t" + message);
    }

    /**
     * @brief Prints a message to the serial port
     * @param message String to print on serial port
     * @param newline Whether to print a newline after the message
     * @param overwrite Whether to overwrite the current line
     * @return void
     */
    void success(String message, bool newline = true, bool overwrite = false)
    {
        if (overwrite)
            Message::overwrite();
        if (newline)
            Serial.println("✅\t" + message);
        else
            Serial.print("✅\t" + message);
    }

    /**
     * @brief Prints a message to the serial port
     * @param message String to print on serial port
     * @return void
     */
    void warning(String message)
    {
        Serial.println("⚠️\t" + message);
    }

    /**
     * @brief Prints a message to the serial port
     * @param message String to print
     * @return void
     */
    void error(String message)
    {
        Serial.println("🚩\t" + message);
    }
}
