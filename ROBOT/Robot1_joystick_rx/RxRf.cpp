// SimpleTx - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "Arduino.h"


void radioSetup(RF24 radio, byte* rfAddress, char * ackData, int channel=108, bool enableAck=true, int retry_count=5, int retry_delay=3) {

    radio.begin();
    radio.setChannel(channel);
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate( RF24_250KBPS );

    radio.openReadingPipe(1, rfAddress);
    
    if(enableAck){
      radio.enableAckPayload();
      radio.writeAckPayload(1, ackData, sizeof(ackData));
    }
    radio.startListening();

}


//====================
int getData(RF24 radio, char * ackData,Point* dataReceived,  boolean enableAck=true) {
    if ( radio.available() ) {
        radio.read( dataReceived, sizeof(Point) );
//        Serial.print(dataReceived.x);
//        Serial.print(" - ");
//        Serial.print(dataReceived.y);
//        Serial.print(" - ");
//        Serial.println(dataReceived.b);
        if (enableAck){
            radio.writeAckPayload(1, &ackData, sizeof(ackData)); // load the payload for the next time
        }
       return 1;
    }
    return 0;
}

void send(RF24 radio, int data, char *ackData) {

    bool rslt;
    rslt = radio.write( &data, sizeof(data) );
      // Always use sizeof() as it gives the size as the number of bytes.
      // For example if dataToSend was an int sizeof() would correctly return 2

    Serial.print("Sent:");
    Serial.print(data);
    if (rslt) {
      if ( radio.isAckPayloadAvailable() ) {
              radio.read(&ackData, sizeof(ackData));
       }
       else {
            Serial.println("  No ACK received ");
       }
       Serial.print("  - ACK:");
       Serial.println(ackData);
    }
    else {
        Serial.println("  Tx failed");
    }
}



