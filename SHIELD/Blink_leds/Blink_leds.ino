/* Define shift register pins used for seven segment display */
#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8
 
/* Segment byte maps for numbers 0 to 9 */
//const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90, 0x88, 0x80, 0xC6, 0xC0, 0x86, 0x8E};
/* Byte maps to select digit 1 to 4 */

const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};
 
void setup ()
{
/* Set DIO pins to outputs */
pinMode(LATCH_DIO,OUTPUT);
pinMode(CLK_DIO,OUTPUT);
pinMode(DATA_DIO,OUTPUT);
}
 
/* Main program */
long counter = 0;
int d = 0;
void loop()
{
 

/* Update the display with the current counter value */
if (d > 15){
  counter = 0;
  d = 10;
}
if(counter % 1000 == 0){
   d++;
  
}
WriteNumberToSegment(0 , d);
WriteNumberToSegment(1 , d);
WriteNumberToSegment(2 , d);
WriteNumberToSegment(3 , d);
counter++;

}
 
/* Write a decimal number between 0 and 9 to one of the 4 digits of the display */
void WriteNumberToSegment(byte Segment, byte Value)
{
digitalWrite(LATCH_DIO,LOW);
shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
digitalWrite(LATCH_DIO,HIGH);
}

