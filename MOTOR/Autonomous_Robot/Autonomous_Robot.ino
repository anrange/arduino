/*
  Relay work build on top of the Mega2560
  Control the relay from the PC
  https://developer.android.com/adk/index.html
  
*/

//Values for the L298N Driver
//http://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/
#define EN1 3 
#define M1_1 2  
#define M1_2 4

#define EN2 6
#define M2_1 8 
#define M2_2 7

// the setup function runs once when you press reset or power the board
void setup() {
  
  //initialize serial for debugging
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  //setup the pins for the motors
  setup_motor();
  
}

void setup_motor(){
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(M1_1, OUTPUT);
  pinMode(M1_2, OUTPUT);
  pinMode(M2_1, OUTPUT);
  pinMode(M2_2, OUTPUT);
}

void moveMotor(int m, bool en, bool dir){
// m is 1 -> motor 1, 2 -> motor 2
// en -> defaults to tru
// dir -> true: fwd, false: rwd
  int _en = EN1, ma = M1_1, mb = M1_2;
  if ( m != 1){
    _en = EN2;
    ma = M2_1;
    mb = M2_2;
  }
  
  if (en){
    digitalWrite(_en, HIGH);
    if (dir){
      digitalWrite(ma, HIGH);
      digitalWrite(mb, LOW);  
    }
    else{
      digitalWrite(ma, LOW);
      digitalWrite(mb, HIGH);  
    }
  }
  else{
    digitalWrite(_en, LOW);
  }
}

void loop() {
  
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
  Serial.println("Motor V1");
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("M1 fwd");
  moveMotor(1,true, true);
    moveMotor(2,true, true);
  delay(7000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("M1 rwd");
  moveMotor(1,true, false);
  moveMotor(2,true, false);
  delay(7000);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("M1 stop");
  moveMotor(1,false, true);
  moveMotor(2,false, true);
  delay(5000);
}
