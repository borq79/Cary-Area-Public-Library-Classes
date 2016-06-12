
// We'll be controlling the motor from pin 9.
// This must be one of the PWM-capable pins.

const int motorPin = 9;
const int sensorPin = 0;

void setup()
{
  // Set up the motor pin to be an output:

  pinMode(motorPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  // Set up the serial port:

  Serial.begin(9600);
}


void loop()
{
  // Because analogWrite() only works with numbers from
  // 0 to 255, we'll be sure the input is in that range:

  int sensorValue = analogRead(sensorPin);
  sensorValue = 1024 - sensorValue; // invert
  int motorSpeed = sensorValue / 4;
  
  motorSpeed = constrain(motorSpeed, 0, 255);
    
 
  Serial.print("Setting speed to ");
  Serial.println(motorSpeed);

  // And finally, we'll set the speed of the motor!
    
  analogWrite(motorPin, motorSpeed);

}



