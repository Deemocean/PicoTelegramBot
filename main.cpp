#include "web_service.h"
#include "sensor_service.h"

#define BOT_TOKEN "XXXXXXX:XXXXXXXXXXXXXXXXXXX"
#define WIFI_SSID "XXXXXXXXXXXXXXXX"
#define WIFI_PASSWORD "XXXXXX"
#define SDA_PIN XX
#define SCL_PIN XX


// TelegramBot Settings
X509List* cert = new X509List(TELEGRAM_CERTIFICATE_ROOT);
BearSSL::WiFiClientSecure* secured_client = new BearSSL::WiFiClientSecure();

UniversalTelegramBot bot(BOT_TOKEN, *secured_client);
// UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done
const unsigned long BOT_MTBS = 1000; //time between scan messages

//Sensor Settings
Adafruit_SHT4x sht4 = Adafruit_SHT4x();
sensors_event_t humidity, temp;

//WiFi Settings
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

void setup()
{
    Serial.begin(115200);
    if (!Serial)
    {
        blink(2, 500);
    }

    Wire.setSCL(SCL_PIN);
    Wire.setSDA(SDA_PIN);
    pinMode(LED_BUILTIN, OUTPUT);

    sensor_init(&sht4, SHT4X_HIGH_PRECISION, SHT4X_NO_HEATER);

    secured_client->setTrustAnchors(cert); // Add root certificate for api.telegram.org

    WiFi_connect(ssid, password);
    clock_sync();

    blink(3,100);
}



void loop()
{

    if (millis() - bot_lasttime > BOT_MTBS)
    {
        Serial.print("Scanning...");
        unsigned long time_start= millis();
        //Serial.printf("WiFi Status: %i\n", WiFi.status());
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        float scan_time = (millis() - time_start) / 1000.0;
        Serial.printf("Took %2f seconds\n", scan_time);
        Serial.printf("%i messages available\n",numNewMessages);
        if(scan_time>15){
            reset();
        }
        while (numNewMessages)
        {
            sht4.getEvent(&humidity, &temp);
            digitalWrite(LED_BUILTIN, HIGH);
            Serial.println("got response");
            handleNewMessages(&bot,temp.temperature, humidity.relative_humidity, numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
            digitalWrite(LED_BUILTIN, LOW);
        }
        bot_lasttime = millis();
    }else{
        //blink(1,500);
        //Serial.print(millis()-bot_lasttime);
        //Serial.println(" ideling...");
    }
}

