#include <web_service.h>

WiFiServer* webserver_create(int port){

    WiFiServer* pserver = new WiFiServer(port);

    return pserver;
}

void WiFi_connect(const char* ssid, const char* password)
{
    
    WiFi.mode(WIFI_STA);
    WiFi.setHostname("CORA");
    Serial.printf("Connecting to '%s' with '%s'\n", ssid, password);
    WiFi.begin(ssid, password);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.printf("\nConnected to WiFi\n\nIP Address: %s\n", WiFi.localIP().toString().c_str());
    return;
}

void clock_sync(void){
    NTP.begin("pool.ntp.org", "time.nist.gov");

    Serial.print("Waiting for NTP time sync: ");
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2)
    {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    Serial.println("");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    Serial.print("Current time: ");
    Serial.print(asctime(&timeinfo));
}

void handleNewMessages(UniversalTelegramBot *bot, float temp, float hum, int numNewMessages)
{
    Serial.println("handleNewMessages");
    Serial.println(String(numNewMessages));

    for (int i = 0; i < numNewMessages; i++)
    {
        String chat_id = bot->messages[i].chat_id;
        String text = bot->messages[i].text;
        String from_name = bot->messages[i].from_name;

        if (from_name == "")
            from_name = "Guest";

        if (text == "/start")
        {
            String welcome = "This is CORA, a bot built by Mr. Unchained, " + from_name + ".\n";
            welcome += "/home_info : Checkout Mr.Unchained's home sensor info\n";
            bot->sendMessage(chat_id, welcome);
        }

        if (text == "/home_info")
        {
            bot->sendChatAction(chat_id, "typing");
            //delay(500);
            
            String data_res = "Room Data: \nTemperature: " + String(temp) + " C\nHumidity: " + String(hum) + "% rH";
            bot->sendMessage(chat_id, data_res);
        }

        if (text == "真的")
        {
            String ya = "正确的, " + from_name + "\n";
            bot->sendMessage(chat_id, ya);
        }
    }
}