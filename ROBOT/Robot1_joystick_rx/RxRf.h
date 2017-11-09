#ifndef RxRf_h
#define RxRf_h

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


typedef struct{
  int x;
  int y;
  int b;
}Point;


void radioSetup(RF24 radio, const byte* rfAddress, char* ackData, int channel, bool enableAck, int retry_count, int retry_delay);

int getData(RF24 radio, char * ackData, Point *data, boolean enableAck=true);

void radioSetup(RF24 radio, const byte* rfAddress, char* ackData);


#endif
