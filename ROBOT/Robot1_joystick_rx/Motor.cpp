/*
  Joystick.cpp - Library for managing a Joystick
  Created by Andres Rangel, October 25, 2017.
  Released into the public domain.
  Vr. 1.0
*/

#include "Arduino.h"
#include "Motor.h"


Joystick::Joystick(int swx,int swy, int swbutton){
  _swx = swx;
  _swy = swy;
  _swbutton = swbutton;
  posx = -1;
  posy = -1;
  button = -1;
}

void Joystick::begin(){
  pinMode(_swx, INPUT); // analog
  pinMode(_swy, INPUT); // analog
  pinMode(_swbutton, INPUT_PULLUP); //digital
}

void Joystick::read(){
  posx = analogRead(_swx);
  posy = analogRead(_swy);
  button = digitalRead(_swbutton);
}

