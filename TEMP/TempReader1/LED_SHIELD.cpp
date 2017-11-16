/* Define shift register pins used for seven segment display */
#include "LED_SHIELD.h"



MultiLED::MultiLED(int latch_DIO, int clk_DIO, int data_DIO){
  latch_dio = latch_DIO;
  clk_dio = clk_DIO;
  data_dio = data_DIO;
}
MultiLED::MultiLED(){
  latch_dio = LATCH_DIO;
  clk_dio = CLK_DIO;
  data_dio = DATA_DIO;
}

void MultiLED::begin(){
/* Set DIO pins to outputs */
    pinMode(latch_dio,OUTPUT);
    pinMode(clk_dio,OUTPUT);
    pinMode(data_dio,OUTPUT);
}
 
 
/*
 * Write a decimal number between 0 and 9 to one of the 4 digits of the display 
 * segment: 0 - 3 (the display segments)
 * Value: 0 - 9 
 * 
 */
void MultiLED::writeDigitToSegment(byte segment, byte value)
{
    digitalWrite(latch_dio,LOW);
    shiftOut(data_dio, clk_dio, MSBFIRST, SEGMENT_MAP[value]);
    shiftOut(data_dio, clk_dio, MSBFIRST, SEGMENT_SELECT[segment] );
    digitalWrite(latch_dio,HIGH);
}

void MultiLED::writeEmptySegment(byte segment)
{
    digitalWrite(latch_dio,LOW);
    shiftOut(data_dio, clk_dio, MSBFIRST, SEGMENT_EMPTY);
    shiftOut(data_dio, clk_dio, MSBFIRST, SEGMENT_SELECT[segment] );
    digitalWrite(latch_dio,HIGH);
}
/*
 * Write a number to the 4 digit display.
 * Starts from left to right
 */
void MultiLED::writeNumber(int num){
  if(num != number){
    int unit=-1, tenth=-1, hundreds=-1,decimal=-1;
    number = num;
    unit = number % 10;
    if (number > 10){
      tenth = ((number / 10) % 10);
      if (number >= 100){
        hundreds = ((number / 100) % 10);
      }
    }
    
    writeDigitToSegment(2, unit);
    delay(10);
    writeDigitToSegment(1, tenth);
//    if(tenth == -1){
//      writeEmptySegment(1);
//    }
//    else{
//      writeDigitToSegment(1, tenth);
//    }
  //  if(hundreds == -1){
  //    writeEmptySegment(0);
  //  }else{
  //    writeDigitToSegment(0, hundreds);
  //  }
   }
  
}



