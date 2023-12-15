// include the library code

#define DETECTION_DISTANCE 200 //Distance that counts as detection

//distance variables for each sensor
int dist1 = 0;
int dist2 = 0;
int dist3 = 0;
int dist4 = 0;
int dist5 = 0;

int lastSensor = 3;
int highSensor = 0;
bool change = false;


void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  Serial.println("#S|STARTPPTX|[]#"); // Tell inbetweeno to start the Powerpoint Application
}

void loop() {
  delay(100); // Maybe not neccesasary
  
  //TODO: Calculate distances
  dist1 = 0;
  dist2 = 0;
  dist3 = 0;
  dist4 = 0;
  dist5 = 0;

  highSensor = sensorcheck();

  if (highSensor != lastSensor && highSensor !=0){
    if(highSensor>lastSensor){ //a new sensor closer to the end has been trigered
      Serial.println("#S|SENDK|[0&{RIGHT}]#");
    }
    else{ //a new sensor closer to the start has been trigered
      Serial.println("#S|SENDK|[0&{LEFT}]#");
    }
    lastSensor = highSensor;
    change = true;
    //TODO: multiple steps if a sensor is skipped
  }

  switch(lastSensor) { //maybe not needed anymore
    case 0:
      // no change 
      break;
    case 1: //closest sensor #941100 (ROT)
      break;
    case 2: //#7030A0 (VIOLETT)
      break;
    case 3: //#005493 (DUNKELBLAU);
      break;
      case 4: //#8DD4FB (HELLBLAU)
      break;
      case 5: //furthest Sensor #FFFFFF (WEIẞ)
      break;
    default: //should not happen
      break;
  }
  if (change){
    //flicker prevention
    delay (400);
    change = false;
  }
}

int sensorcheck() {
  if (dist1 < DETECTION_DISTANCE && dist1 != 0){ //closest sensor
  //  Serial.println("sensor 1");
    return 1;
  } else if (dist2 < DETECTION_DISTANCE && dist2 != 0) {
  //  Serial.println("sensor 2");
    return 2;
  } else if (dist3 < DETECTION_DISTANCE && dist3 != 0) {
  //  Serial.println("sensor 3");
    return 3;
  } else if (dist4 < DETECTION_DISTANCE && dist4 != 0) {
  //  Serial.println("sensor 4");
    return 4;
  } else if (dist5 < DETECTION_DISTANCE && dist5dw != 0) {
  //  Serial.println("sensor 5");
    return 5;
  } else { //no sensor detectects anything
  //  Serial.println("no sensor"); 
    return 0;
  }
}
