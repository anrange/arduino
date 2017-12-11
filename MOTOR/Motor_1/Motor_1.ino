/*
  Relay work build on top of the Mega2560
  Control the relay from the PC
  https://developer.android.com/adk/index.html
  
*/
#include"Arduino.h"
// Defining the calues for the ultra sound sensor.
#define TRIG 4
#define ECHO 5

//Values for the L298N Driver
//http://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/
#define EN1 3
#define M1_1 A5  
#define M1_2 A4

#define EN2 10
#define M2_1 A3
#define M2_2 A2





// the setup function runs once when you press reset or power the board
void setup() {
  //initialize serial
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
//  pinMode(TRIG, OUTPUT);
//  pinMode(ECHO, INPUT);

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(M1_1, OUTPUT);
  pinMode(M1_2, OUTPUT);
  pinMode(M2_1, OUTPUT);
  pinMode(M2_2, OUTPUT);
  

}


int incomingByte = 0;   // for incoming serial data

int printLed(int pin, int val){

  
  digitalWrite(pin, val);   // turn the LED on (HIGH is the voltage level)
  return !val;
  
}
//http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
long readDistance(){

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(ECHO, HIGH);
  // Calculating the distance 
  return duration;
  
}

void moveMotor(int m, bool en, bool dir){
// m is 1 -> motor 1, 2 -> motor 2
// en -> defaults to tru
// dir -> true: fwd, false: rwd
  int _en = EN1, ma = M1_1, mb = M1_2;
  if ( m != 1){
    _en = EN2;
    ma = M2_1;
    mb = M2_2;
  }
  
  if (en){
    digitalWrite(_en, HIGH);
    if (dir){
      digitalWrite(ma, HIGH);
      digitalWrite(mb, LOW);  
    }
    else{
      digitalWrite(ma, LOW);
      digitalWrite(mb, HIGH);  
    }
  }
  else{
    digitalWrite(_en, LOW);
  }
}

//rf module http://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/

int tmp = 0;

int readCommand(){
  
  int incomingByte = 0;
  int tmp = 0;
  Serial.print("Press 1 to read, 0 to exit");  
  do{
    incomingByte = Serial.read();
    tmp = incomingByte >0? incomingByte - 48: incomingByte;
    if (tmp == 1){
      long dist = readDistance();
      Serial.print("\nRaw: ");
      Serial.print(dist);
      Serial.print("- Distance:");
      Serial.println(dist*0.034/2);
    }
    else if (tmp == 0){
      Serial.println("Good Bye ");
      return -1;
    }
    else{
      delay(100);
      Serial.print(".");
    }
  }while(true);
  return -1;
}

int readCommandMotor(){
  
  int incomingByte = 0;
  int tmp = 0;
  Serial.print("Press 1 to read, 0 to exit");  
  do{
    incomingByte = Serial.read();
    tmp = incomingByte >0? incomingByte - 48: incomingByte;
    if (tmp == 1){
      long dist = readDistance();
      Serial.print("\nRaw: ");
      Serial.print(dist);
      Serial.print("- Distance:");
      Serial.println(dist*0.034/2);
    }
    else if (tmp == 0){
      Serial.println("Good Bye ");
      return -1;
    }
    else{
      delay(100);
      Serial.print(".");
    }
  }while(true);
  return -1;
}

void loop() {
  
  
//  digitalWrite(TRIG, LOW);
//  digitalWrite(EN1, LOW);
//  digitalWrite(EN2, LOW);

  Serial.println("Motor V1");
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("M1 fwd");
  moveMotor(1,true, true);
  moveMotor(2,true, true);
  delay(7000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("M1 rwd");
  moveMotor(1,true, false);
  moveMotor(2,true, false);
  delay(7000);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("M1 stop");
  moveMotor(1,false, true);
  moveMotor(2,false, true);
  delay(500);
}
