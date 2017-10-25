/*
  Radio.cpp - Library for managing de radio
  Helper functions with the radio
  Created by Andres Rangel, October 25, 2017.
  Released into the public domain.
*/

#include "arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

char ackData[] = "Acknowledge";

void setupRadio(RF24 radio, bool enableAck, int retry_count=5, int retry_delay=3, int channel=-1){
  radio.begin();
  if (channel == -1){
    //to reduce wifi interference
    channel = 108;
  }
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate( RF24_250KBPS );

  if(enableAck){
    radio.enableAckPayload();
    radio.writeAckPayload(1, ackData, sizeof(ackData));
  }
  radio.setRetries(retry_delay,retry_count); // delay, count
  
}

void setupRadioWriting(RF24 radio, char* address){
  radio.openWritingPipe(slaveAddress[0]);
}



