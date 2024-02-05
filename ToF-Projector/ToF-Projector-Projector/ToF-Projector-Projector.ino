// include the library code
#include <Wire.h>
#include <VL53L1X.h>

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define DETECTION_DISTANCE 3000 //Distance that counts as detection

//I/O Constants
#define IN_1      14
#define IN_2      15
#define IN_3      16
#define IN_4      17

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int volume = 10;
unsigned long startTime = 0;

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

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor.startContinuous(50);
}

void loop() {
  dist = sensor.read();
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
      volume = volume -3;
      myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
    }
      else{ //a new sensor closer to the end has been trigered
      Serial.println("#S|SENDK|[0&{RIGHT}]#");
      volume = volume +3;
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
    return 5;
  } else if (sensor3) {
    return 4;
  } else if (sensor2) {
    return 3;
  } else if (sensor1) {
    return 2;
  } else if (sensor0) { //closest sensor
  startTime = millis();
    return 1;

  } else { //no sensor detectects anything
    if (millis() - startTime > 2000  && lastSensor ==1){
      lastSensor = -1;
      Serial.println("#S|SENDK|[0&{LEFT}]#");
      volume = volume -2;
      myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
    }
    return 0;
  }
}

bool areSensorsAdjacent(int sensor1, int sensor2) {
  if (sensor2 == -1){

    //handle special State
    if (sensor1=1){
      Serial.println("#S|SENDK|[0&{RIGHT}]#");
      lastSensor=1;
      volume = volume +3;
      myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
      return false;
    }else if (sensor1 = 2){
      Serial.println("#S|SENDK|[0&{RIGHT}]#");
      Serial.println("#S|SENDK|[0&{RIGHT}]#");
      lastSensor=2;
      volume = volume +6;
      myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
      return false;
    }
  }
  return abs(sensor1 - sensor2) == 1;
}