// include the library code
//TODO: Sound-library

#define KNOCKPIN        8    // Arduino pin tied to the Knock-Sensor

int shock = 0; //initialize the variable shock as 0 TODO: could use for error handling

void setup() {
  
  pinMode(KNOCKPIN,INPUT); //initialize Knock-Sensor as an input

}

void loop() {

  shock = digitalRead(KNOCKPIN); //read the value from Knock-Sensor
  //TODO: multiple Sensors
  Serial.println(shock);

  if(shock == LOW)  //with vibration signal
  {
    //TODO: Sound
  }

}
