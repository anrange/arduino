#ifndef LED_SHIELD_H
#define LED_SHIELD_H

/* Define shift register pins used for seven segment display */
#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8
#include "Arduino.h"
/* Segment byte maps for numbers 0 to 9 */
const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
const byte SEGMENT_EMPTY = 0x00;
/* Byte maps to select digit 1 to 4 */
const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};
#include "Arduino.h"

class MultiLED
{
  public:
    MultiLED();
    MultiLED(int latch_dio, int clk_dio, int data_dio);
    void begin();
    void writeDigitToSegment(byte segment, byte value);
    void writeEmptySegment(byte segment);
    void writeNumber(int num);
     
  private:
     int latch_dio, clk_dio, data_dio;
};
#endif
