/*
  Created by Andres Rangel, August 25, 2018.
  Released into the public domain.
  Vr. 1.0
*/
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
 *     
 *     To use it you can either press the button or access it through the web server:
 *     http://${IR_IP}:8080/on. 
 *     
 *     You can create an alias in the command line for easy debugging:
 *     alias a='curl http://${IR_IP}:8080/on'
 */

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

void printToDisplay(String);
void appendToDisplay(String);
//pin out
#define IR_LED 4  // ESP8266 GPIO pin to use. Recommended: 4 (D4).
#define PUSH_BUTTON 5  // push button 5 (D5).
#define LED 12  // LED pin//

const char* ssid = "NULL"; // replace NULL with "SSID";
const char* password = "NULL"; // replace NULL with "password";
const int TVON = 0xa90;

#define IP_RETURN 5
#define ERROR_RETURN -1
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(8080); 
IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.

void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  delay(10);

  // prepare GPIO2
  pinMode(PUSH_BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  

  // Connect to WiFi network
  printToDisplay("\n\n");
  
  // Initialising the display for IP
  printToDisplay("Initializing screen");
  
  if (ssid == NULL || password == NULL) {
    printToDisplay("Initializing screen");
    exit(0);
  }

  printToDisplay("Connecting to ");
  printToDisplay(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    appendToDisplay(".");
  }
  printToDisplay("");
  printToDisplay("WiFi connected");

  // Start the server
  server.begin();
  printToDisplay("Server started");

  // Print the IP address
  IPAddress ip = WiFi.localIP();

  printToDisplay("IP:" + ip.toString());
}

void loop() {
  digitalWrite(LED, LOW);
  int push = digitalRead(PUSH_BUTTON);
    if (push == LOW){
      printIP();
      on_off();
    }
  // Check if a client has connected
  WiFiClient client = server.available();

  if (client){
    
  
    // Wait until the client sends some data
    printToDisplay("new client");
    while (!client.available()) {
      delay(1);
    }
  
    // Read the first line of the request
    String req = client.readStringUntil('\r');
    Serial.println(req);
    client.flush();
    
    // Match the request
    int val = ERROR_RETURN;
    if (req.indexOf("/on") != -1) {
      
      val = on_off();

      
    
    
    } else {
      client.stop();
      printToDisplay("invalid request");
      
    }
    if (val != IP_RETURN && val != ERROR_RETURN){
      printToDisplay(req);
    }
  
    client.flush();
  
    // Prepare the response
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
    s += (val == 0 || val == IP_RETURN) ? "success" : "failure";
    s += "</html>\n";
  
    // Send the response to the client
    client.print(s);
    delay(1);
    Serial.println("Client disonnected");
  
    // The client will actually be disconnected
    // when the function returns and 'client' object is detroyed
  }
  
}

int on_off() {
    printToDisplay("Sending ON/OFF Command (Sony Protocol)");
    irsend.sendSony(TVON, 12, 2);
    digitalWrite(LED, HIGH);
    return 0;
}


void printToDisplay(String text) {
    Serial.println(text);    
}

void appendToDisplay(String text){
  Serial.print(text);    
}

int printIP(){
  IPAddress ip = WiFi.localIP();
  printToDisplay("IP:" + ip.toString());
  return IP_RETURN;
}

