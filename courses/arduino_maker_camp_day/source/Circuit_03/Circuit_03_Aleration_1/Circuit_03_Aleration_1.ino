
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

const int SENSOR_PIN = 0;


void setup()
{
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

  int intensity = 255 - (sensorValue / 4);
  
  analogWrite(RED_PIN, intensity);
  analogWrite(BLUE_PIN, intensity);
  analogWrite(GREEN_PIN, intensity);
}

