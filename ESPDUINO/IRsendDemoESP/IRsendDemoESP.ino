/* IRremoteDemoESP
 *
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by IR_LED below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/markszabo/IRremoteESP8266/wiki#ir-sending
 *     Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 *     
 *     
 *     **************
 *     
 *     I have a NPN transistor (BC548) with a resistor (100 ohm) to 5V in series with
 *     the LED_IR in series with the Catode (pin 1.) The base has a resistor of 1.2 k
 *     that conects directly to the ESPDUINO output pin (IR_LED). The Emisor is conected 
 *     to ground. 
 *     
 *     I added a push button using the pull up resistor on GPIOD5, that triggers the sending
 *     of the command. 
 *     The command is 0xa90 using sony protocol, sine that is what SCEPTRE uses (tv I have)
 *     
 *     There an led conected in series to ground through a 330 ohm resistor to identify when 
 *     we are sending the command.
 */

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>

#define IR_LED 4  // ESP8266 GPIO pin to use. Recommended: 4 (D4).
#define PUSH_BUTTON 5  // push button 5 (D5).
#define LED 12  // LED pin

IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.


void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  pinMode(PUSH_BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
int push = digitalRead(PUSH_BUTTON);
if (push == LOW){
      Serial.println("Sending ON Command (Sony Protocol)");
      irsend.sendSony(0xa90, 12, 1);
      digitalWrite(LED, HIGH);
      delay(100);    
}
else{
  digitalWrite(LED, LOW);

}
}
