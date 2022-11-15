#pragma once

#include <ESP8266WiFiMulti.h>
#include <optional>

#ifdef NETWORK_H
#define EXTERN
#else
#define EXTERN extern
#endif

extern std::optional<int> G_issueCount;

// Define global varable for WiFiMulti
EXTERN ESP8266WiFiMulti G_wifiMulti;
