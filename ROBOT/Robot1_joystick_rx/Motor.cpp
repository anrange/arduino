/*
  Joystick.cpp - Library for managing a Joystick
  Created by Andres Rangel, October 25, 2017.
  Released into the public domain.
  Vr. 1.0
*/

#include "Arduino.h"
#include "Motor.h"

//Values for the L298N Driver
//http://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/


DualMotor::DualMotor(int enable1,int ma1, int ma2, int enable2, int mb1, int mb2, int trigger_pin, int echo_pin){
  en1 = enable1;
  en2 = enable2;
  dira1 = ma1;
  dirb1 = mb1;
  dira2 = ma2;
  dirb2 = mb2;

  //proximity sensor
  proximitySensor = new UltraSound(trigger_pin, echo_pin);

  x = 514;
  y = 500;
}

void DualMotor::begin(){
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(dira1, OUTPUT);
  pinMode(dira2, OUTPUT);
  pinMode(dirb1, OUTPUT);
  pinMode(dirb2, OUTPUT);

  proximitySensor->begin();

}


void DualMotor::move(Point p){
   move(p.x,p.y);
}
void DualMotor::move(){
   move(x,y);
}
void DualMotor::move(int _x, int _y){
  x = _x;
  y = _y;
  

  int direction = STOP;
  if ((x >LOWRANGE && x < HIGHRANGE) && (y >LOWRANGE && y < HIGHRANGE)){
    stopMotor();
    Serial.println("Stoping motor");
    return;
  }

  if (x >LOWRANGE && x < HIGHRANGE){
    //x is stop
    if (y <= LOWRANGE){
      moveFwd();
      Serial.println("FWD");     
    }
    else{
      moveBack();
      Serial.println("BACK");
    }
    return;
  }

  if (y >LOWRANGE && y < HIGHRANGE){
    //y is stop (left or right
    if (x <= LOWRANGE){
      rotateRight();
      Serial.println("RIGHT");
    }
    else{
      rotateLeft();
      Serial.println("LEFT");
    }
  }
  else{
//both are in the range
     //move them in place
     if (x <= LOWRANGE){
          moveLeft();
          Serial.println("LEFT");
     }
     else{
        moveRight();
        Serial.println("RIGHT");
     }     
 }
}

void DualMotor::moveFwd(){
  //both motors should move forward
  if(proximitySensor->isThereObstacle()==false){
     moveMotor(1,true, true);
     moveMotor(2,true, true);
  }
  else{
    //stop
    stopMotor();
  }
}

void DualMotor::moveBack(){
  //both motors should move forward
   moveMotor(1,true, false);
   moveMotor(2,true, false);
}


void DualMotor::rotateLeft(){
  //m1 should move back
   moveMotor(1,true, false);
  //m2 should fwd
   moveMotor(2,true, true);
  
}

void DualMotor::rotateRight(){
  //m1 should move forward
   moveMotor(1,true, true);
  //m2 should move backward
   moveMotor(2,true, false);
  
}

void DualMotor::moveLeft(){
  if(!proximitySensor->isThereObstacle()){
    //m1 should move forward
     moveMotor(1,true, true);
    //m2 should stop
     moveMotor(2,false, false);
  }
  else{
    stopMotor();
  }
  
}

void DualMotor::moveRight(){
  if(!proximitySensor->isThereObstacle()){
    //m1 should stop
     moveMotor(1,false, false);
    //m2 should move forward
     moveMotor(2,true, true);
  }
  else{
    stopMotor();
  }
}

void DualMotor::stopMotor(){
  //m2 & m1 should stop
   moveMotor(2,false, false);
  //m1 should stop
   moveMotor(1,false, false);
  
}

/* m is 1 -> motor 1, 2 -> motor 2
 * en -> defaults to true
 * dir -> true: fwd, false: rwd
*/
void DualMotor::moveMotor(int m, bool en, bool dir){
  int _en = en1, ma = dira1, mb = dira2;
  if ( m != 1){
    _en =  en2;
    ma =  dirb1;
    mb = dirb2;
  }
  
  if (en){
    //moving the motor
    digitalWrite(_en, HIGH);
    if (dir){ //fwd . 
      digitalWrite(ma, HIGH);
      digitalWrite(mb, LOW); 
    }
    else{ //back
      digitalWrite(ma, LOW);
      digitalWrite(mb, HIGH);  
    }
  }
  else{ //stop
    digitalWrite(_en, LOW);
    digitalWrite(ma, LOW);
    digitalWrite(mb, LOW);
  }
}






