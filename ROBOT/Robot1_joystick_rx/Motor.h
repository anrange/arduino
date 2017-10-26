/*
  Joystick.h - Library for managing a Joystick
  Created by Andres Rangel, October 25, 2017.
  Released into the public domain.
  Vr. 1.0
*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Joystick
{
  public:
    Joystick(int swx,int swy, int swbutton);
    void begin();
    void read();
    int posx, posy,button;
  private:
    int _swx,_swy,_swbutton;
};

#endif

