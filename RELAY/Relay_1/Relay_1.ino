/*
  Relay work build on top of the Mega2560

  
*/

// the setup function runs once when you press reset or power the board
void setup() {
  //initialize serial
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  

}

int printLed(int pin, int val){
  
  
  digitalWrite(pin, val);   // turn the LED on (HIGH is the voltage level)
  return !val;
  
}

void loop() {
  Serial.print("Value is ");
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  delay(5000);
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(5000);
  
}
