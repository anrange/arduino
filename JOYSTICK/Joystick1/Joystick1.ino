
#include "Joystick.h"
//#include "Radio.cpp"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SWX A0
#define SWY A1
#define SWBUTTON  8

Joystick joystick(SWX, SWY, SWBUTTON);

void setup() {
 
  Serial.begin(9600);
  Serial.println("Joystick 1");
  joystick.begin();
}




void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("calling readJoysTick");
  
  joystick.read();
  Serial.print("Button:");
  Serial.print(joystick.button);
  Serial.print(" | X:");
  Serial.print(joystick.posx);
  Serial.print(" , Y:");
  Serial.println(joystick.posy);
  delay(1000);
  
  
  

}
