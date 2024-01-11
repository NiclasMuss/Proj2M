// include the library code
#include "Arduino.h"
//Music librarys
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
//Ultrasonic library
#include <NewPing.h>

//Ultrasonic constants
#define TRIGGER_PIN     14     // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN        15     // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE    400   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define DETECTION_DISTANCE 20 //Distance that counts as detection

//I/O constants
#define OUT  8

//Music variables
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
bool music = false;
void printDetail(uint8_t type, int value);

//Ultrasonic variables
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int dist = 0;

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(115200); //IMPORTANT: Influences Motor speed
  pinMode(OUT,OUTPUT); //initialize output-pin
  digitalWrite(OUT, LOW);

  //Starting the Music player
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(0);  //Set volume value. From 0 to 30 (start on 0)
  myDFPlayer.play(1);  //Play the first mp3
  }

void loop() {

  //Ultrasonic ping
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  dist = uS / US_ROUNDTRIP_CM; //convert to cm
  //print the Ping
  Serial.print("Ping: ");
  Serial.print(dist);
  Serial.println("cm");

  //change the volume depending on the ultrasonic ping
  if(dist < DETECTION_DISTANCE){
    myDFPlayer.volume(10);  //Set volume value. From 0 to 30
    digitalWrite(OUT,HIGH);
  }
  else{
    myDFPlayer.volume(0);  //Set volume value. From 0 to 30
    digitalWrite(OUT,LOW);
  }
  delay(50);
}