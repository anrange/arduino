/*
  Joystick.h - Library for managing a Joystick
  Created by Andres Rangel, October 25, 2017.
  Released into the public domain.
  Vr. 1.0
*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

#define STOP 0
#define FWD 1
#define BWD 2
#define LEFT 3
#define RIGHT 4
#define LOWRANGE 300
#define HIGHRANGE 700
class DualMotor
{
  public:
    DualMotor(int en1,int dira1, int dira2, int en2, int dirb1, int dirb2);
    void begin();
    void move(int x, int y);
    void move();
    void moveMotor(int m, bool en, bool dir);
    void moveFwd();
    void moveBack();
    void moveLeft();
    void moveRight();
    void stopMotor();
    void rotateRight();
    void rotateLeft();
    int x,y;
    
  private:
    int en1,en2, dira1, dira2, dirb1, dirb2;
};

#endif

