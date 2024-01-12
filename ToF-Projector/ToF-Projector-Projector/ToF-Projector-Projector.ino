// include the library code
#include <Wire.h>
#include <VL53L1X.h>

#define DETECTION_DISTANCE 1300 //Distance that counts as detection

//I/O Constants
#define IN_1      14
#define IN_2      15
#define IN_3      16
#define IN_4      17

//ToF variables
VL53L1X sensor;
int dist = 0;

//variables for the recieved Sensor Data
int sensor0 = 0;
int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  //set the I/O Pins
  pinMode(IN_1,INPUT);
  pinMode(IN_2,INPUT);
  pinMode(IN_3,INPUT);

  sensor.setTimeout(500);
  if (!sensor.init())
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

  //read the input from the other Sensors
  sensor1 = digitalRead(IN_1);
  sensor2 = digitalRead(IN_2);
  sensor3 = digitalRead(IN_3);
  sensor4 = digitalRead(IN_4);

  //Debug Grid
  Serial.print(sensor0);
  Serial.print(sensor1);
  Serial.print(sensor2);
  Serial.print(sensor3);
  Serial.print(sensor4);

  Serial.println();
}