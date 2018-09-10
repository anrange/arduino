/*
  WifiCreds.cpp - Library for managing the wifi credentials from the eeprom
  Created by Andres Rangel, Sept 7, 2018.
  Released into the public domain.
  Vr. 1.0
  How to use:
  * You must run the begin function on your setup method.
  * The write command will automatically commit it to the eeprom.
  * 
*/

#include "Arduino.h"
#include "WifiCreds.h"

WifiCreds::WifiCreds(){
   char empty[CHAR_SIZE] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
   strncpy(ssid, empty, CHAR_SIZE);
   strncpy(password, empty, CHAR_SIZE);    
}

void WifiCreds::write(const char *ss, const char *passw){
   this->write(0, ss, passw);
}
void WifiCreds::write(int address, const char *ss, const char *passw){
   strncpy(ssid, ss, CHAR_SIZE);
   strncpy(password, passw, CHAR_SIZE);   
   Serial.println("Will write: "+String(this->ssid)+","+String(this->password));  
   EEPROM.put(address, *this);
   EEPROM.commit(); 
}

void WifiCreds::begin(){
  EEPROM.begin(512);
  
}
void WifiCreds::reload(){  
  reload(0);
}

void WifiCreds::reload(int address){  
  EEPROM.get(address, *this);
}

