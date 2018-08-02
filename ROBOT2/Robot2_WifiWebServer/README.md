Need to add SSID and password before uploading.
After startup, display shows ip.

Commands are:

CAR_IP=<ip shown on display after startup>
alias w='curl http://${CAR_IP}:8080/forward'
alias x='curl http://${CAR_IP}:8080/backward'
alias s='curl http://${CAR_IP}:8080/stop'
alias d='curl http://${CAR_IP}:8080/right'
alias a='curl http://${CAR_IP}:8080/left'

ESPDUINO:
Install following instructions at https://arduino-esp8266.readthedocs.io/en/2.4.1/installing.html#using-git-version
Some more info here: https://github.com/SmartArduino/SZDOITWiKi/wiki/Arduino---ESPduino

CHASSIS:
Motor pins:
Green to D4 (D4 on the breadboard shield)
Blue to D5 (D5 on the breadboard shield)

Yellow to D0 (D2 on the breadboard shield)
Orange to D2 (D3 on the breadboard shield)

Power pins from chassis:
Green (long with round plastic shield at the end) to Gnd
Red (from switch with black tape and round plastic shield at the end) to Vin


DISPLAY:
https://www.aliexpress.com/item/1-3-inch-OLED-IIC-I2C-128X64-White-LCD-LED-Display-Module/32816642029.html
Need to use SH1106
Add library esp8266-oled-ssd1306 to Arduino IDE as follows:
Sketch->Include Library->Manage Libraries->Search for "esp8266 and esp32 oled driver for SSD1306 display" by Daniel Eichhorn, Fabrice Weinberg
Source code is at https://github.com/ThingPulse/esp8266-oled-ssd1306
Pins:
Vcc and Gnd wherever you have room for Vcc and Gnd
SDA -> D3 (D11 on the breadboard shield)
SCL -> D1 (D12 on the breadboard shield)



