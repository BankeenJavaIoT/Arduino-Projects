/*
* written by Bankeen Mustafa
* a project for Java IoT course, in IntecBrussel
* 20/09/2019
*/
const int temperaturePin = A0;
const int ledColdPin = 11;
const int ledNormalPin = 12;
const int ledHotPin = 13;

const int COLD_HIGH_LIMIT = 20;
const int HOT_LOW_LIMIT = 30;

void setup()
{
  Serial.begin(9600);
  pinMode(ledColdPin, OUTPUT);
  pinMode(ledNormalPin, OUTPUT);
  pinMode(ledHotPin, OUTPUT);
}


void loop()
{
  float voltage, degreesC;  
  voltage = getVoltage(temperaturePin);  
  degreesC = getTemprature(voltage, 36); // 36 designates to TMP36 sensor
    
  Serial.print(degreesC);
  Serial.println("   C° ");

  updateLeds(degreesC);
  
  delay(1000); // repeat once per second (change as you wish!)
}

float getTemprature(float voltage, int sensorType) {
  switch (sensorType) {
    case 35: return (625.5/6.0) * voltage - (25.0/18.0); break;
    case 36: return 100.0 * voltage - 50.0; break;
    case 37: return 50.0 * voltage; break;
  }  
}

float getVoltage(int pin)
{
  return (5.0 / 1024.0) * analogRead(pin);  
  // This equation converts the 0 to 1023 value that analogRead()
  // returns, into a 0.0 to 5.0 value that is the true voltage
  // being read at that pin.
}

void updateLeds(float degreeC) {
  int cold = LOW;
  int normal = LOW;
  int hot = LOW;
  if (degreeC < COLD_HIGH_LIMIT) {
    cold = HIGH;
  } else 
  if (degreeC < HOT_LOW_LIMIT) {
    normal = HIGH;
  } else {
    hot = HIGH;
  }   
  digitalWrite(ledColdPin, cold);
  digitalWrite(ledNormalPin, normal);
  digitalWrite(ledHotPin, hot);
}
