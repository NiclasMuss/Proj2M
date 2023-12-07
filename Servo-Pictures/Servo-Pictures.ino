#include <Servo.h>

Servo myServo;         // Create a Servo object
int buttonPin = 4;      // Pin for the button
int buttonState = 0;    // Variable to store the button state
int servoState = 0;     // Variable to store the current state of the servo

void setup() {
  Serial.begin(2400);
  myServo.attach(9);    // Attach the servo to pin 9
  pinMode(buttonPin, INPUT);  // Set the button pin as INPUT
}

void loop() {
  // Read the state of the button
  buttonState = digitalRead(buttonPin);
  Serial.print(buttonState);

  // If the button is pressed, toggle the servo state
  if (buttonState == HIGH) {
    myServo.write(0);    // Move to 0 degrees
    Serial.println("High");
    delay(1000);
  } else {
    myServo.write(180);    // Move to 0 degrees
    Serial.println("Low");
    delay(1000);
  } 
}
