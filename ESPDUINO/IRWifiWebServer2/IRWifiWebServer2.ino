/*
  Created by Andres Rangel, August 25, 2018.
  Released into the public domain.
  Vr. 1.1
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
//Libraries for the web server
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//libraries for the IR remote
#include <IRremoteESP8266.h>
#include <IRsend.h>

//For the eeprom
#include <WifiCreds.h>

void printToDisplay(String);
void appendToDisplay(String);
// definition of pin out/in
#define IR_LED 4  // ESP8266 GPIO pin to use. Recommended: 4 (D4).
#define PUSH_BUTTON 5  // push button 5 (D5).
#define LED 12  // LED pin//

//constant variable used within the code
const int TVON = 0xa90; // turn tv of/on
const int TVSRC = 0xA50; // source command
const int TVDWN = 0xAF0; // move down 
const int TVSET = 0xD10; // ok/set
const int TVVOLUP = 0x490; // volume up
const int TVVOLDOWN = 0xC90; // volume down
const int TVCHNUP = 0x90; // channel up
const int TVCHNDOWN = 0x890; // channel down


#define IP_RETURN 5
#define ERROR_RETURN -1
// Create an instance of the server
// specify the port to listen on as an argument
ESP8266WebServer server(8080);

//Defining the IR sender on the defined port.
IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.

//Define the credes class to read from eeprom
WifiCreds creds;

//this method handles the "root /" command on the server.
void handleRoot() {
  digitalWrite(LED, 1);
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf(temp, 400,

           "<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <img src=\"/test.svg\" />\
  </body>\
</html>",

           hr, min % 60, sec % 60
          );
  server.send(200, "text/html", temp);
  digitalWrite(LED, 0);
}

//Handles for all the paths not found
void handleNotFound() {
  digitalWrite(LED, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(LED, 0);
}

void handleTVOn(){
  digitalWrite(LED, HIGH);
  on_off();

  String message = "Executing TV ON/OFF command\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\n";
  
  server.send(200, "text/plain", message);
  digitalWrite(LED, LOW);
}

void handleRoku(){
  digitalWrite(LED, HIGH);

  printToDisplay("Sending ROKU Command (Sony Protocol)");
   // send source first
  irsend.sendSony(TVSRC, 12, 2);
  delay(200);
  irsend.sendSony(TVDWN, 12, 2);
  delay(200);
  irsend.sendSony(TVDWN, 12, 2);
  delay(200);
  irsend.sendSony(TVDWN, 12, 2);
  delay(200);
  irsend.sendSony(TVSET, 12, 2);

  String message = "Executing ROKU command\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\n";
  
  server.send(200, "text/plain", message);
  digitalWrite(LED, LOW);
}

void handleVolumeUp(){
  digitalWrite(LED, HIGH);

  printToDisplay("Sending Volume UP Command (Sony Protocol)");
   // send source first
  irsend.sendSony(TVVOLUP, 12, 2);
  
  String message = "Executing Volume UP command\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\n";
  
  server.send(200, "text/plain", message);
  digitalWrite(LED, LOW);
}

void handleVolumeDown(){
  digitalWrite(LED, HIGH);

  printToDisplay("Sending Volume Down Command (Sony Protocol)");
   // send source first
  irsend.sendSony(TVVOLDOWN, 12, 2);
  
  String message = "Executing Volume Down command\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\n";
  
  server.send(200, "text/plain", message);
  digitalWrite(LED, LOW);
}


void handleChannelUp(){
  digitalWrite(LED, HIGH);

  printToDisplay("Sending Channel UP Command (Sony Protocol)");
   // send source first
  irsend.sendSony(TVCHNUP, 12, 2);
  
  String message = "Executing Channel UP command\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\n";
  
  server.send(200, "text/plain", message);
  digitalWrite(LED, LOW);
}

void handleChannelDown(){
  digitalWrite(LED, HIGH);

  printToDisplay("Sending Channel Down Command (Sony Protocol)");
   // send source first
  irsend.sendSony(TVCHNDOWN, 12, 2);
  
  String message = "Executing Channel Down command\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\n";
  
  server.send(200, "text/plain", message);
  digitalWrite(LED, LOW);
}


void setup() {
  irsend.begin();
  creds.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  delay(10);

  // prepare GPIO2
  pinMode(PUSH_BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  

  // Connect to WiFi network
  printToDisplay("\n\n");
  
  // Initialising the display for IP
  printToDisplay("Initializing screen");
  
  creds.reload();
  if (strlen(creds.ssid) < 2 || strlen(creds.password) < 2) {
    printToDisplay("Need to set ssid ** password in the eeprom.");
    exit(0);
  }

  printToDisplay("Connecting to ");
  printToDisplay(creds.ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(creds.ssid, creds.password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    appendToDisplay(".");
  }
  printToDisplay("");
  printToDisplay("WiFi connected");

  // Start the server
  server.on("/", handleRoot);
  server.on("/test.svg", drawGraph);
  server.on("/on", handleTVOn);
  server.on("/roku", handleRoku);
  server.on("/volume/up", handleVolumeUp);
  server.on("/volume/down", handleVolumeDown);
  server.on("/channel/up", handleChannelUp);
  server.on("/channel/down", handleChannelDown);
  
  server.onNotFound(handleNotFound);
  server.begin();
  printToDisplay("Server started");

  // Print the IP address
  IPAddress ip = WiFi.localIP();
  printToDisplay("HTTP server started \nIP:" + ip.toString());
}

void loop() {
  int push = digitalRead(PUSH_BUTTON);
  if (push == LOW){
    digitalWrite(LED, HIGH);
    printIP();
    on_off();
    digitalWrite(LED, LOW);

  }
  server.handleClient();
}

int on_off() {
    printToDisplay("Sending ON/OFF Command (Sony Protocol)");
    irsend.sendSony(TVON, 12, 2);
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

void drawGraph() {
  String out = "";
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10) {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send(200, "image/svg+xml", out);
}
