/*
  Created by Andres Rangel, August 1, 2018.
  Released into the public domain.
  Vr. 1.0
*/

#include <ESP8266WiFi.h>
#include "SH1106.h"

//pin out
#define LEFT_MOTOR_PIN1 0
#define LEFT_MOTOR_PIN2 2
#define RIGHT_MOTOR_PIN1 4
#define RIGHT_MOTOR_PIN2 5
#define PUSH_BUTTON 13
#define LED_SDA 3
#define LED_SCL 1
//

const char* ssid = NULL; // replace NULL with "SSID";
const char* password = NULL; // replace NULL with "password";

#define IP_RETURN 5
#define ERROR_RETURN -1
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(8080);

SH1106Wire display(0x3c, LED_SDA, LED_SCL);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(PUSH_BUTTON, INPUT);
  stop();

  // Connect to WiFi network
  Serial.println();
  Serial.println();

  // Initialising the display for IP
  Serial.println("Initializing screen");
  display.init();
  display.flipScreenVertically();

  if (ssid == NULL || password == NULL) {
    Serial.println("Initializing screen");
    printToDisplay("ERROR: please add wifi info");
    exit(0);
  }

  printToDisplay("Initialized screen.");

  printToDisplay("Connecting to " + String(ssid));

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  printToDisplay("IP:" + ip.toString());
}

void loop() {
  int push = digitalRead(PUSH_BUTTON);
    if (push == HIGH){
      printIP();
    }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val = ERROR_RETURN;
  if (req.indexOf("/stop") != -1) {
    val = stop();
  } else if (req.indexOf("/forward") != -1) {
    val = forward();
  } else if (req.indexOf("/backward") != -1) {
    val = backward();
  } else if (req.indexOf("/right") != -1) {
    val = right();
  } else if (req.indexOf("/left") != -1) {
    val = left();
  } else if (req.indexOf("/ip") != -1) {
    val = printIP();  
  } else {
    Serial.println("invalid request");
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

int stop() {
    digitalWrite(LEFT_MOTOR_PIN1, 0);
    digitalWrite(LEFT_MOTOR_PIN2, 0);
    digitalWrite(RIGHT_MOTOR_PIN1, 0);
    digitalWrite(RIGHT_MOTOR_PIN2, 0);
    return 0;
}

int forward() {
    digitalWrite(LEFT_MOTOR_PIN1, 1);
    digitalWrite(LEFT_MOTOR_PIN2, 0);
    digitalWrite(RIGHT_MOTOR_PIN1, 1);
    digitalWrite(RIGHT_MOTOR_PIN2, 0);
    return 0;
}

int backward() {
    digitalWrite(LEFT_MOTOR_PIN1, 0);
    digitalWrite(LEFT_MOTOR_PIN2, 1);
    digitalWrite(RIGHT_MOTOR_PIN1, 0);
    digitalWrite(RIGHT_MOTOR_PIN2, 1);
    return 0;
}

int left() {
    digitalWrite(LEFT_MOTOR_PIN1, 1);
    digitalWrite(LEFT_MOTOR_PIN2, 0);
    digitalWrite(RIGHT_MOTOR_PIN1, 0);
    digitalWrite(RIGHT_MOTOR_PIN2, 1);
    return 0;
}

int right() {
    digitalWrite(LEFT_MOTOR_PIN1, 0);
    digitalWrite(LEFT_MOTOR_PIN2, 1);
    digitalWrite(RIGHT_MOTOR_PIN1, 1);
    digitalWrite(RIGHT_MOTOR_PIN2, 0);
    return 0;
}

void printToDisplay(String text) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, text);
    display.display();
}

int printIP(){
  IPAddress ip = WiFi.localIP();
  printToDisplay("IP:" + ip.toString());
  return IP_RETURN;
}

