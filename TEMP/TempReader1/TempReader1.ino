#include "Arduino.h"
#include <max6675.h>
#include "LED_SHIELD.h"
/**
 * Obtained from:
 * http://henrysbench.capnfatz.com/henrys-bench/arduino-temperature-measurements/max6675-temp-module-arduino-manual-and-tutorial/
 */
int ktcSO = 5;
int ktcCS = 6;
int ktcCLK = 9;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
MultiLED multiLED; // intialize the led segments on default ports
  
void setup() {
  Serial.begin(9600);
  // give the MAX a little time to settle
  multiLED.begin();

  cli();//stop interrupts
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
  
  
  delay(500);
}





boolean first = true;
int value = 0;
void loop() {
  // basic readout test
  if (first){
    read_value();
    first = false;
  }
  multiLED.writeNumber(value);
   
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz , reads temperature
    read_value();
//  counter();
}

void counter(){
    value++;
    if(value >= 999){
      value = 0;
    }

}

void read_value(){
  Serial.print("Deg C = "); 
  Serial.print(ktc.readCelsius());
  Serial.print("\t Deg F = ");
  value = (int)ktc.readFahrenheit();
  Serial.println(value);
}

