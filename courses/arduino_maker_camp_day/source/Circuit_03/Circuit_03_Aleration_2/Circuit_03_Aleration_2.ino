
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

const int SENSOR_PIN = 0;


void setup()
{
  Serial.begin(9600);
  
  // Here we'll configure the Arduino pins we're using to
  // drive the LED to be outputs:

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
}


void loop()
{
  int sensorValue = analogRead(SENSOR_PIN); 
  int halfSensroValue = sensorValue / 2;

  int redCurveValue = abs(halfSensroValue - 255);
  int blueCurveValue = (510 - abs(sensorValue - 510)) / 2;
  int greenCurveValue = (255 - abs(sensorValue - 510)) / 2;

  //Serial.print(sensorValue); Serial.print(":"); Serial.println(blueCurveValue);
  //delay(2000);
  
  analogWrite(RED_PIN, redCurveValue);
  analogWrite(BLUE_PIN, blueCurveValue);
  analogWrite(GREEN_PIN, greenCurveValue);
}

