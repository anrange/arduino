/*
  Relay work build on top of the Mega2560
  Control the relay from the PC
  https://developer.android.com/adk/index.html
  
*/
// the setup function runs once when you press reset or power the board


#define TRIG 4
#define ECHO 5
// the setup function runs once when you press reset or power the board
void setup() {
  //initialize serial
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  

}


int incomingByte = 0;   // for incoming serial data

int printLed(int pin, int val){

  
  digitalWrite(pin, val);   // turn the LED on (HIGH is the voltage level)
  return !val;
  
}
//http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
long readDistance(){

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(ECHO, HIGH);
  // Calculating the distance 
  return duration;
  
}

//rf module http://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/

int tmp = 0;

int readCommand(){
  
  int incomingByte = 0;
  int tmp = 0;
  Serial.print("Press 1 to read, 0 to exit");  
  do{
    incomingByte = Serial.read();
    tmp = incomingByte >0? incomingByte - 48: incomingByte;
    if (tmp == 1){
      long dist = readDistance();
      Serial.print("\nRaw: ");
      Serial.print(dist);
      Serial.print("- Distance:");
      Serial.println(dist*0.034/2);
    }
    else if (tmp == 0){
      Serial.println("Good Bye ");
      return -1;
    }
    else{
    //  turnOffPins();  
      delay(100);
      Serial.print(".");
    }
  }while(true);
  return -1;
}

void loop() {
  
  
  digitalWrite(TRIG, LOW);
  Serial.println("Distance V1.0");
  delay(100);
  readCommand();
}
