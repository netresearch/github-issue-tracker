namespace Mqtt
{

    /***
     * @brief Setup the MQTT class
     * @return void
     */
    void setup();

    /**
     * @brief Publish a message to the MQTT broker
     * @param payload The message to publish
     * @return void
     */
    void publish(const char *payload);

    /**
     * @brief Replace characters in a string
     *
     * @see https://arduinojson.org/v6/faq/how-to-use-arduinojson-with-pubsubclient/
     *@param str Original string
     *@param orig Character to replace
     *@param rep Replacement character
     *@return int Number of replacements
     */
    int replaceChar(char *str, char orig, char rep);
}
