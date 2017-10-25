
#include "Joystick.h"
#include "Radio.cpp"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SWX A0
#define SWY A1
#define SWBUTTON  8
#define CE_PIN   9
#define CSN_PIN 10

Joystick joystick(SWX, SWY, SWBUTTON);

void setup() {
 
  Serial.begin(9600);
  Serial.println("Joystick 1");
  joystick.begin();
}

void send(int ) {

    bool rslt;
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2

    Serial.print("Data Sent ");
    Serial.print(dataToSend);
    if (rslt) {
      if ( radio.isAckPayloadAvailable() ) {
              radio.read(&ackData, sizeof(ackData));
              newData = true;
       }
       else {
            Serial.println("  Acknowledge but no data ");
       }
       updateMessage();
    }
    else {
        Serial.println("  Tx failed");
    }
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
