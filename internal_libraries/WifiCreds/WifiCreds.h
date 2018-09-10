/*
  WifiCreds.h - Library for managing the wifi credentials from the eeprom
  Created by Andres Rangel, Sept 7, 2018.
  Released into the public domain.
  Vr. 1.0
  How to use:
  * You must run the begin function on your setup method.
  * The write command will automatically commit it to the eeprom.
  * To read from the eeprom, just call the "reload" command.
  * 
*/

#ifndef WifiCreds_h
#define WifiCreds_h
#include "Arduino.h"
#include <EEPROM.h>
#define CHAR_SIZE 20
class WifiCreds{
  public:
    WifiCreds ();
    void begin();
    void reload();
    void reload(int address);
    void write(const char *ss, const char *passw);
    void write(int address, const char *, const char *);
    
    char ssid[CHAR_SIZE];
    char password[CHAR_SIZE];
  
}; 



#endif
