// include the library code
#include <Wire.h>
#include <VL53L1X.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define DETECTION_DISTANCE 1300 //Distance that counts as detection

//I/O Constants
#define IN_1      14
#define IN_2      15
#define IN_3      16
#define IN_4      17

//Mp3-Variables
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int volume = 1;

//ToF variables
VL53L1X sensor;
int dist = 0;

//variables for the recieved Sensor Data
int sensor0 = 0;
int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;

int lastSensor = 0;
int highSensor = 0;
bool change = false;

void setup() {
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3

  Serial.begin(115200);
  Serial.println("#S|STARTPPTX|[]#"); // Tell gobetweeno to start the Powerpoint Application
  Wire.begin();
  Wire.setClock(400000);

  //set the I/O Pins
  pinMode(IN_1,INPUT);
  pinMode(IN_2,INPUT);
  pinMode(IN_3,INPUT);
  pinMode(IN_4,INPUT);

  sensor.setTimeout(500);
  if (!sensor.init()) //inititalize Sensor
  {
    Serial.print("Failed to detect and initialize sensor!");
    while (1);
  }
  //maybe use long distance in example?

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor.startContinuous(50);
}

void loop() {
  dist = sensor.read();
  //Serial.print(dist);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  //check own Sensor
  if (dist<=DETECTION_DISTANCE){
    //Serial.print("DETECTED");
    sensor0 = 1;
  } else{
    sensor0 = 0;
  }
  //sensor0 = (dist <= DETECTION_DISTANCE) ? 1 : 0;

  //read the input from the other Sensors
  sensor1 = digitalRead(IN_1);
  sensor2 = digitalRead(IN_2);
  sensor3 = digitalRead(IN_3);
  sensor4 = digitalRead(IN_4);

  highSensor = sensorcheck();

  if (highSensor != lastSensor && highSensor !=0){
    if (areSensorsAdjacent(highSensor, lastSensor)){
      if(highSensor<lastSensor){ //a new sensor closer to the start has been trigered
      Serial.println("#S|SENDK|[0&{LEFT}]#");
      //turn the volume down
      volume = volume -2;
      myDFPlayer.volume(volume);  
    }
      else{ //a new sensor closer to the end has been trigered
      Serial.println("#S|SENDK|[0&{RIGHT}]#");
      //turn the volume up
      volume = volume +2;
      myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
    }
    lastSensor = highSensor;
    change = true;
    }
    
  }

  //Debug Grid
  /*
  Serial.print(sensor0);
  Serial.print(sensor1);
  Serial.print(sensor2);
  Serial.print(sensor3);
  Serial.print(sensor4);

  Serial.println();
  */
}

int sensorcheck() {
  if (sensor4){ //futhest sensor
  //  Serial.println("sensor 4");
    return 5;
  } else if (sensor3) {
  //  Serial.println("sensor 3");
    return 4;
  } else if (sensor2) {
  //  Serial.println("sensor 2");
    return 3;
  } else if (sensor1) {
  //  Serial.println("sensor 1");
    return 2;
  } else if (sensor0) { //closest sensor
  //  Serial.println("sensor self");
    return 1;
  } else { //no sensor detectects anything
  //  Serial.println("no sensor"); 
    return 0;
  }
}

bool areSensorsAdjacent(int sensor1, int sensor2) {
  if (sensor2 == 1.5){
    //handle special State
  }
  return abs(sensor1 - sensor2) == 1;
}