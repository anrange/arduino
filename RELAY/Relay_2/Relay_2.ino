/*
  Relay work build on top of the Mega2560
  Control the relay from the PC
  https://developer.android.com/adk/index.html
  
*/
// the setup function runs once when you press reset or power the board

#define RED 4
#define YELLOW 3
#define BLUE 2

void setup() {
  //initialize serial
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);

}



int incomingByte = 0;   // for incoming serial data

int printLed(int pin, int val){

  
  digitalWrite(pin, val);   // turn the LED on (HIGH is the voltage level)
  return !val;
  
}

void turnOffPins(){
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(BLUE, LOW);
}
int tmp = 0;

int selectLight(){
  
  int incomingByte = 0;
  int tmp = 0;
  Serial.print("What led to print: 1). Red, 2). YELLOW 3). Blue 4). Clear\n");  
  do{
    incomingByte = Serial.read();
    tmp = incomingByte >0? incomingByte - 48: incomingByte;
    if (tmp == 1){
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, LOW);
      digitalWrite(YELLOW, LOW);
    }
    else if (tmp == 2){
      digitalWrite(YELLOW, HIGH);
      digitalWrite(BLUE, LOW);
      digitalWrite(RED, LOW);
    }
    else if (tmp ==3){
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, HIGH);
      digitalWrite(YELLOW, LOW);
    }
    else{
    //  turnOffPins();
      delay(100);
      Serial.print(".");
    }
  }while(incomingByte < 0);
  return incomingByte;
}


int selectLightBin(){
  
  int incomingByte = 0;
  int tmp = 0;
  Serial.print("What led to print: 1). Red, 2). YELLOW 3). Blue 4). Clear\n");  
  int red,blue,yellow = LOW;
  do{
    incomingByte = Serial.read();
    tmp = incomingByte >0? incomingByte - 48: incomingByte;

    if (tmp >= 0){
      red = ((tmp & 1) > 0 ? HIGH:LOW);
      yellow = ((tmp & 2) > 0 ? HIGH:LOW);
      blue = ((tmp & 4) > 0 ? HIGH:LOW);
      digitalWrite(RED, red);
      digitalWrite(BLUE, blue);
      digitalWrite(YELLOW, yellow);

      Serial.print("\nB Y R->");
      Serial.print(blue);
      Serial.print(yellow);
      Serial.println(red);
    }
    else{ 
    //  turnOffPins();
      delay(100);
      Serial.print(".");
    }
  }while(incomingByte < 0);
  return incomingByte;
}
void loop() {
  
  
  int incomingByte = selectLightBin();
  Serial.print("Got:");
  Serial.println(incomingByte);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  delay(5000);
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(5000);
  
}
