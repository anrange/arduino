#ifndef TxRf_h
#define TxRf_f

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


void radioSetup(RF24 radio, byte* rfAddress, char * ackData, int channel=108, bool enableAck=true, int retry_count=5, int retry_delay=3);
void send(RF24 radio, int data, char *ackData);

#endif
