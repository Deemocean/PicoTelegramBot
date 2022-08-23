#include <WiFi.h>
#include <time.h>
#include "UniversalTelegramBot.h"

// returns a server pointer with the destinated port
WiFiServer *webserver_create(int port); 
// connect to the wifi
void WiFi_connect(const char *ssid, const char *passphrase);
// syncs onboard clock to NTP
void clock_sync(void);
//telegram bot handles new messages
void handleNewMessages(UniversalTelegramBot* bot,float temp, float hum, int numNewMessages);
