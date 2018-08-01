
#include "Motor.h"
#include "RxRf.h"
#include "UltraSound.h"

#define CE_PIN 7
#define CSN_PIN 8

#define EN1 3                                   
#define DIRA_1 2
#define DIRA_2 4

#define EN2 6
#define DIRB_1 9
#define DIRB_2 10

#define TRIGGER_PIN 1
#define ECHO_PIN 5

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
char ackData[10] = "123456789"; // to hold the two values coming from the slave
bool newData = false;
char dataReceived[12];


const byte slaveAddress[5] = {'T','x','N','I','C'};

DualMotor motor(EN1,DIRA_1, DIRA_2, EN2, DIRB_1, DIRB_2, TRIGGER_PIN, ECHO_PIN);

void setup() {
 
  Serial.begin(9600);
  Serial.println("Joystick 1");
  //radioSetup(radio, slaveAddress, ackData);
  motor.begin();
}




void loop() {
  // put your main code here, to run repeatedly:
  //readData();
  motor.move(500,1000);
  delay(1000);
//  readData();
  
}

void readData(){
//  int dataReceived[3];
  Point _point;
  int v = getData(radio, ackData, &_point);
  if (v != 0){
      Serial.print(_point.x); 
      Serial.print(" - "); 
      Serial.print(_point.y); 
      Serial.print(" - "); 
      Serial.print(_point.b); 
      Serial.print(" - ");
      motor.move(_point.x, _point.y);
      long d = motor.proximitySensor->readDistance();
      Serial.println(d);
      Serial.println(motor.proximitySensor->isThereObstacle());
  }
  else{
//    Serial.print(" Didn't receive ");
//    motor.move();
  }
//  Serial.println(" ******** "); 
}


