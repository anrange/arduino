#ifndef UltraSound_h
#define UltraSound_h

#include "arduino.h"

class UltraSound
{
  public:
    UltraSound(int trigger,int echo);
    void begin();
    long readDistance();
    boolean isThereObstacle();
    int trigger,echo;
    long OBSTACLE_LIMIT;

};
#endif

