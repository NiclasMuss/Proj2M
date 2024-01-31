/*
  Proj2-M WS 2023/24
  Knock-Textiles Software
  Author: Niclas Muss
*/

// include the library code
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define KNOCKPIN  8 // the number of the first knock sensor pin
#define KNOCKPIN2  7 // the number of the second knock sensor pin

//Mp3-Player Objects
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// variable for reading the knock sensor status (HIGH = no knock detected)
int knockState = HIGH;
int knockState2 = HIGH;

void setup() 
{
  // initialize the knock sensor pins as input: 
  pinMode(KNOCKPIN, INPUT);
  pinMode(KNOCKPIN2, INPUT);
  //inititalize the Mp3-Player
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

void loop()
{
  knockState = digitalRead(KNOCKPIN); // read the state of the knock sensor value:
  if (knockState == LOW)
  {
    myDFPlayer.play(1);  //Play the first mp3
    delay(2000);
  }

  knockState2 = digitalRead(KNOCKPIN2); // read the state of the knock sensor value:
  if (knockState2 == LOW)
  {
    myDFPlayer.play(2);  //Play the second mp3
    delay(2000);
  }
}


