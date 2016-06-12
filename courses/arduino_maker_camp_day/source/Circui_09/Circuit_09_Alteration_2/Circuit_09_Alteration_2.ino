
  
const int buzzerPin = 9;
const int sensorPin = 0;

const unsigned int maxFreq = 2048;
const unsigned int minFreq = 31;

unsigned int freqRange = maxFreq - minFreq;
unsigned int stepSize = (freqRange / 1024) + 1;


void setup() 
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensorPin, INPUT);
}


void loop() 
{
  unsigned int sensorValue = analogRead(sensorPin);
  sensorValue = 1023 - sensorValue; // invert
 
  unsigned int freq = stepSize * sensorValue;

  tone(buzzerPin, freq); 
}
