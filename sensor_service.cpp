#include "sensor_service.h"

void sensor_init(Adafruit_SHT4x* sht4, sht4x_precision_t prec, sht4x_heater_t heat){
    if (!sht4->begin())
    {
        while (1)
        {
            Serial.println("Couldn't find SHT4x");
            delay(500);
        }
    }

    Serial.println("Found SHT4x sensor");
    Serial.print("Serial number 0x");
    Serial.println(sht4->readSerial(), HEX);
    sht4->setPrecision(prec);
    sht4->setHeater(heat);
}

void blink(int num_blink, int delay_time){
    for (int i = 0; i < num_blink; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(delay_time);
        digitalWrite(LED_BUILTIN, LOW);
        delay(delay_time);
    }
    return;
}