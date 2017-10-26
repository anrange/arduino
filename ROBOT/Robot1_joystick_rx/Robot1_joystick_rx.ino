#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>


#include "Motor.h"
#include "RxRf.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char ackData[10] = "123456789"; // to hold the two values coming from the slave
bool newData = false;
char dataReceived[12];
int pos[3];


const byte slaveAddress[5] = {'T','x','N','I','C'};

#define SWX A0
#define SWY A1
#define SWBUTTON  8



void setup() {
 
  Serial.begin(9600);
  Serial.println("Joystick 1");
  radioSetup(radio, slaveAddress, ackData);

}




void loop() {
  // put your main code here, to run repeatedly:
  readData();
  readData();
  readData();
  delay(500);
}

void readData(){
  int dataReceived[3];
  Point _point;
  int v = getData(radio, ackData, &_point);
  if (v != 0){
      Serial.print(_point.x); 
      Serial.print(" - "); 
      Serial.print(_point.y); 
      Serial.print(" - "); 
      Serial.print(_point.b); 
      Serial.print(" - "); 
  }
  else{
    Serial.print(" Didn't receive "); 
  }
  Serial.println(" ******** "); 
}


