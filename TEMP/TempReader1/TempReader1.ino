#include "Arduino.h"
#include <max6675.h>
#include "LED_SHIELD.h"
/**
 * Obtained from:
 * http://henrysbench.capnfatz.com/henrys-bench/arduino-temperature-measurements/max6675-temp-module-arduino-manual-and-tutorial/
 */
int ktcSO = 5;
int ktcCS = 6;
int ktcCLK = 9;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
MultiLED multiLED; // intialize the led segments on default ports
  
void setup() {
  Serial.begin(9600);
  // give the MAX a little time to settle
  multiLED.begin();
  delay(500);
}
long count = 0;
int value = 0;
void loop() {
  // basic readout test
   
   
   if( count %500 == 0 || count == 0){
     Serial.print("Deg C = "); 
     Serial.print(ktc.readCelsius());
     Serial.print("\t Deg F = ");
     value = (int)ktc.readFahrenheit();
     Serial.println(value);
     
   }
   count ++;
   multiLED.writeNumber(value);
   
   
}
