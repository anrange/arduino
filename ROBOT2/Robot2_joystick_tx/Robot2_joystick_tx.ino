
#include "Joystick.h"
#include "TxRf.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend[10] = "Carlito 0";
char txNum = '0';
char ackData[10] = "123456789"; // to hold the two values coming from the slave
bool newData = false;
char dataReceived[12];
int pos[3];


const byte slaveAddress[5] = {'T','x','N','I','C'};

#define SWX A0
#define SWY A1
#define SWBUTTON  8

Joystick joystick(SWX, SWY, SWBUTTON);

void setup() {
 
  Serial.begin(9600);
  Serial.println("Joystick 1");
  radioSetup(radio, slaveAddress, ackData);
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
  sendData();
  delay(2000); 
  
}

void sendData(){
  Serial.println("Sending X-Y-Z");
  Point data;
  data.x = joystick.posx;
  data.y = joystick.posy;
  data.b = joystick.button;
  
  send(radio, data, 3, ackData);
  
  
}


