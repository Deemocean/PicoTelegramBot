# PicoTelegramBot
A Pico W based Telegram Bot sends sensor data(Adafruit SHT40 Temperature/Humidity Sensor) to the Telegram chat

<img width="693" alt="chat" src="https://user-images.githubusercontent.com/39002684/185810305-36546ff7-7ac9-49d9-8dd4-c08f5119e91e.png">

Uses Arduino-Pico Core With `platformio.ini` setting:
```
[env:picow]
platform = https://github.com/maxgerhardt/platform-raspberrypi.git
board = rpipicow
framework = arduino
board_build.core = earlephilhower
lib_deps = 
	adafruit/Adafruit SHT4x Library@^1.0.2
	adafruit/Adafruit BusIO@^1.13.2
	witnessmenow/UniversalTelegramBot@^1.3.0
 ```

<img width="693" alt="chat" src="https://user-images.githubusercontent.com/39002684/185810353-c4d8e754-5d73-40e3-bc3c-97fb6ef5d9f5.JPG">
