# ESPDuino board

The ESPDuino board is an arduino clone that is built on top of the ESP8266 microcontroller.

## Getting Started

You need to first update arduino.
These steps are taken from: https://arduino-esp8266.readthedocs.io/en/latest/
### Installation

Go to: https://arduino-esp8266.readthedocs.io/en/latest/installing.html

The "Boards manager" setup didn't work. You need to follow the "git" setup:
# Go to a directory:
$ cd hardware
$ mkdir esp8266com
$ cd esp8266com
$ git clone https://github.com/esp8266/Arduino.git esp8266

$ mv or cp this folder to the hardware path in Mac. The path on my machine was:
$ cp -R esp8266com ~/Library/Arduino15/packages/esp8266/hardware/
If you have an error about ssl.SSLError: [SSL: TLSV1_ALERT_PROTOCOL_VERSION] tlsv1 alert protocol version then you must update openssl and or python. To do so do this:
 
$ brew update
$ brew upgrade openssl
$ brew upgrade python

### Running the app
* Select Espduino (Esp-13)



## Running the tests

First example is blink_led



##Arduino Uno WIFI 

###Description:
Cloned to the WeMos UNO+ESP8266 board 
Full integration on one board: Uno R3 ATmega 328 and WiFi ESP8266 with memory 32Mb (MegaByte). All of the modules can work together or each separately. And everyone has their own pinout headers.
The convenient solution for the development of new projects requiring Uno and WiFi.
Via USB you can update sketches and firmvare for ATmega328 and for ESP8266. For this on board have the USB-serial converter CH340G.
Use this board is very simple.
The board has DIP-switch, to connect the modules.
For example, to: USB and ATmega328, USB and ESP8266, ATmega328 and ESP8266.
Table DIP- switch:
Connection	DIP
 	                            1	2	3	4	5	6	7
ATmega328<->ESP8266	            ON	ON	OFF	OFF	OFF	OFF	OFF

USB <->ATmega328	            OFF	OFF	ON	ON	OFF	OFF	OFF

USB<->ESP8266               	OFF	OFF	OFF	OFF	ON	ON	ON
(Update firmware or sketch)

USB<->ESP8266 (communication)	OFF	OFF	OFF	OFF	ON	ON	OFF
All independent					OFF	OFF	OFF	OFF	OFF	OFF	OFF


###Package included:

1 x UNO+WiFi R3 ATmega328P+ESP8266 Board 32Mb Memory


###URL to buy it
https://www.banggood.com/UNOWiFi-R3-ATmega328PESP8266-Board-32Mb-Memory-USB-TTL-CH340G-Compatible-For-Arduino-Uno-p-1193957.html?gmcCountry=US&currency=USD&createTmp=1&utm_source=googleshopping&utm_medium=cpc_elc&utm_content=zouzou&utm_campaign=pla-brand-elc2-us&gclid=CjwKCAjwkYDbBRB6EiwAR0T_-sd-pPklOzU_4FxlE3oySezq4UHbnmcSYn74UGiDoSdRAK3lR6e7JRoC1okQAvD_BwE&cur_warehouse=CN


##Links
https://www.arduino.cc/en/Guide/ArduinoUnoWiFi#toc12


## Acknowledgments

* All info from https://arduino-esp8266.readthedocs.io/en/latest/ 



