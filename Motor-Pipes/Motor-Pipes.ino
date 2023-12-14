// include the library code
#include <CheapStepper.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define BUTTONPIN 14 //Arduino pin tiesd to Button (14=A0)

//Motor variable
CheapStepper stepper (2, 3, 4, 5);
boolean moveClockwise = true;
int rotation = 0; //on full rotation is 4096 Steps

//Button variables
int buttonState = HIGH;    // Variable to store the button state

//Music variables
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
bool music =false;
void printDetail(uint8_t type, int value);


void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(115200); //IMPORTANT: Influences Motor speed
  pinMode(BUTTONPIN,INPUT); //initialize vibration switch as an input
  pinMode(BUTTONPIN, INPUT);  // Set the button pin as INPUT
  digitalWrite(BUTTONPIN, HIGH);

  //Starting the Music player
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(0);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
  }

void loop() {
  //TODO: Sound (check for locking behavior or diferent board)
  buttonState = digitalRead(BUTTONPIN);
  //Serial.println(buttonState);
  if(buttonState == LOW){
    myDFPlayer.volume(2);  //Set volume value. From 0 to 30
    while(buttonState == LOW){
      rotateMotor();
      buttonState = digitalRead(BUTTONPIN);
    }
    
  }
  else{
    myDFPlayer.volume(0);  //Set volume value. From 0 to 30
    while(buttonState == HIGH){
      delay(1);
      buttonState = digitalRead(BUTTONPIN);
    }
  }
}

void rotateMotor(){
  stepper.step(moveClockwise);
  rotation = rotation + 1;
  if(rotation > 4096){ //only rotate 360 degrees than turn (maybe not neccesary)
    moveClockwise = !moveClockwise;
    rotation = 0;
  }
}
