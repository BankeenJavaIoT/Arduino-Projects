/*
* written by Bankeen Mustafa
* a project for Java IoT course, in IntecBrussel
* 03/10/2019
*/

#define trigPin 13
#define echoPin 12
#define servoMotorPin 2
#define servoMotorLowLimit 30
#define servoMotorHighLimit 150
#define servoMotorStepValue 1

#include <Servo.h>

Servo myservo;
int pos = 0; 
int currentStepValue = +servoMotorStepValue;

void setup()
{
//  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servoMotorPin);
}

void loop()
{
  pos = getNextPosition(pos);
  myservo.write(pos); 
  int distance = readDistance();
//  Serial.println(distance);
  delay(50);
}

int getNextPosition(int currentPosition) {
  int nextPosition = currentPosition + currentStepValue;  
  if (nextPosition < servoMotorLowLimit) {
    nextPosition = servoMotorLowLimit;
    currentStepValue = +servoMotorStepValue;
  } else if (nextPosition > servoMotorHighLimit) {
    nextPosition = servoMotorHighLimit;
    currentStepValue = -servoMotorStepValue;
  }
  return nextPosition;
}

int readDistance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(5); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
//  Serial.println(duration);
//  Serial.print(" ");
  distance = (duration/2.0) / 29.1;
  return distance;
}
