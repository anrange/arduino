
/*
 * this example works with the specified board
 */
// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN 8

const byte thisSlaveAddress[2][5] = {{'R','x','A','A','A'}, {'S','x','A','A','A'}};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[10]; // this must match dataToSend in the TX
char ackData[10] = "ok ......"; // the two values to be sent to the master
int sizeAckData = 2;
bool newData = false;
char dataToSend[12] = "Jose Muc 0 ";

//===========

void setup() {

    Serial.begin(9600);

    Serial.println("SimpleRxAck Starting");
    radio.begin();
    radio.setChannel(108);
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress[0]);
    radio.enableAckPayload();
    radio.writeAckPayload(1, &ackData, sizeof(ackData)); // pre-load data
    radio.startListening();
}

//=============

void loop() {
    getData();
    showData();
   // sendData();
}

//==============

void getData() {
//    radio.openReadingPipe(1, thisSlaveAddress[0]);
//    radio.startListening();
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        updateReplyData();
        newData = true;
    }
}

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.println(dataReceived);
        newData = false;
    }
}
void sendData(){
    
    radio.stopListening();
    radio.openWritingPipe(thisSlaveAddress[1]);

    
    bool rstl;
    rstl = radio.write( &dataToSend, sizeof(dataToSend));

    if(rstl){
      if (radio.isAckPayloadAvailable()){
        radio.read(&ackData, sizeof(ackData));
        Serial.print("Sent:");
        Serial.println(dataToSend);
        Serial.print("Received ack ");
        Serial.println(ackData);
      }
    }
}

void updateReplyData() {
//    ackData[0] -= 1;
//    ackData[1] -= 1;
//    if (ackData[0] < 100) {
//        ackData[0] = 109;
//    }
//    if (ackData[1] < -4009) {
//        ackData[1] = -4000;
//    }
    int t = dataReceived[8] - '0';
    t--;
    if (t < 0){
      t =9;
    }
    dataReceived[8] = (t + '0');
    radio.writeAckPayload(1, &dataReceived, sizeof(dataReceived)); // send back what was sent
}
