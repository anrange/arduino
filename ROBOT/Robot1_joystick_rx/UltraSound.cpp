#include "Arduino.h"
#include "UltraSound.h"

UltraSound::UltraSound(int trig,int _echo){
  trigger = trig;
  echo = _echo;
  OBSTACLE_LIMIT = 100;
}

void UltraSound::begin(){
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, LOW);
}

long UltraSound::readDistance(){
      
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echo, HIGH);
  // Calculating the distance 
  //distance= duration*0.034/2;

  return duration;  
}
    
boolean UltraSound::isThereObstacle(){
  long dist = readDistance();
  return dist < OBSTACLE_LIMIT ; 
}
    


