// SimpleTx - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "Arduino.h"
#include "TxRf.h"


void radioSetup(RF24 radio, byte* rfAddress, char * ackData, int channel=108, bool enableAck=true, int retry_count=5, int retry_delay=3) {

    radio.begin();
    radio.setChannel(channel);
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate( RF24_250KBPS );

    if(enableAck){
      radio.enableAckPayload();
      radio.writeAckPayload(1, ackData, sizeof(ackData));
    }
    radio.setRetries(retry_delay,retry_count); // delay, count
    radio.openWritingPipe(rfAddress);
}


//====================
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



