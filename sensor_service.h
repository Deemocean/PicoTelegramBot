#include "Adafruit_SHT4x.h"

//initalize sensor, set precision, begin (hanging if sensor failed)
void sensor_init(Adafruit_SHT4x* sht4, sht4x_precision_t prec, sht4x_heater_t heat);
//blinks the onboard LED
void blink(int num_blink, int delay);

void reset(void);
