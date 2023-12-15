// include the library code
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define KNOCKPIN  8    // Arduino pin tied to the Knock-Sensor
#define MP3LENGTH 10000 // Length of the Mp3 file in Milliseconds

int shock = 0; //initialize the variable shock as 0 TODO: could use for error handling

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  
  pinMode(KNOCKPIN,INPUT); //initialize Knock-Sensor as an input
  mySoftwareSerial.begin(9600);
  Serial.begin(57600);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(2);  //Set volume value. From 0 to 30
}

void loop() {

  shock = digitalRead(KNOCKPIN); //read the value from Knock-Sensor
  //TODO: multiple Sensors
  Serial.println(shock);

  if(shock == LOW)  //with vibration signal
  {
    myDFPlayer.play(1);  //Play the first mp3
    delay(MP3LENGTH);
  }
}
