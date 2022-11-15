#pragma once

namespace Message
{
    /**
     * @brief Prints a message to the serial port
     * @param message String to print
     * @return void
     */
    void overwrite(bool clearLine = true);

    /**
     * @brief Prints the logo to the serial port
     * @return void
     */
    void logo();

    /**
     * @brief Prints the bold logo to the serial port
     * @return void
     */
    void logoBold();

    /**
     * @brief Prints a line break to the serial port
     * @return void
     */
    void br();

    /**
     * @brief Prints a message to the serial port
     * @param message To display on serial port
     * @param newline Whether to print a newline after the message
     * @param clearLine Whether to clear the line before printing the message
     * @return void
     */
    void info(String message, bool newline = true, bool overwrite = false);

    /**
     * @brief Prints a message to the serial port
     * @param message String to print
     * @return void
     */
    void data(String message);

    /**
     * @brief Prints a message to the serial port
     * @param message String to print on serial port
     * @param newline Whether to print a newline after the message
     * @return void
     */
    void working(String message, bool newline = true);

    /**
     * @brief Prints a message to the serial port
     * @param message String to print on serial port
     * @param newline Whether to print a newline after the message
     * @param overwrite Whether to overwrite the current line
     * @return void
     */
    void success(String message, bool newline = true, bool overwrite = false);

    /**
     * @brief Prints a message to the serial port
     * @param message String to print on serial port
     * @return void
     */
    void warning(String message);

    /**
     * @brief Prints a message to the serial port
     * @param message String to print
     * @return void
     */
    void error(String message);
}
