
// Analog Pin 0 is what is used to read the voltage levels from the analog pin of the PCB. 
// Possible values are 0 - 1023 where 0 is the brightest and 1023 is the darkest
#define SENSOR_ANALONG_PIN 0

// We will drive 5 PWM pins based on the input from the photoresitor. When using the analog
// output from the PCB, drive the pin as a PWMs so that reflects the brightness of the
// room. 
#define LED_ARRAY_ELEMENT_0 5
#define LED_ARRAY_ELEMENT_1 6
#define LED_ARRAY_ELEMENT_2 9
#define LED_ARRAY_ELEMENT_3 10
#define LED_ARRAY_ELEMENT_4 11

static int ledArray[5] = {LED_ARRAY_ELEMENT_0, LED_ARRAY_ELEMENT_1, LED_ARRAY_ELEMENT_2, LED_ARRAY_ELEMENT_3, LED_ARRAY_ELEMENT_4};
static const int ARRAY_SIZE = sizeof(ledArray) / sizeof(int); 

void setup() {
  // Init the serial communications for debugging messages
  Serial.begin(9600);
  
  // Iterate over the array and set the PWM pins to output
  for(int i = 0; i < ARRAY_SIZE; i++) {
    pinMode(ledArray[i], OUTPUT);
  }
}

void loop() {
  // *** Uncomment this line if the data line runs from A0 on the PCB to A0 on the Arduino
  int brightness = readAnalogSensorPin();
  
  updateLedArray(brightness);
  
  // Add this delay so the output is trottled to something reasonable
  delay(50);
}

int readAnalogSensorPin() {
  // Read the value on the Analog pin - represents the value from the photoresistor PCB. Values are
  // 0 (bright) to 1023 (dark)
  int analogVal = analogRead(SENSOR_ANALONG_PIN);
  
  Serial.println(analogVal); 
  
  return analogVal;
}
 
void updateLedArray(int brightness) {
  // The PWM is 0-255, where 255 is 100% duty cycle and 0 is 0% duty cycle. The photoresistor is brightest when
  // it is a analog value of 0, and darkest when it is 1023. There are more clever ways to do this than 
  // a straight up compare of the ranges, but this is clearer. If you want, you can look into bit shifting and 
  // masking to allow for dynamic array size without changing the algorithim, just the array size.

  
  // Brightness values 820 - 1023 light up LED 0 and the others are off
  // Brightness values 615 - 819 light up LEDs 0 and 1 and the others are off
  // Brightness values 410 - 614 light up LEDs 0-2 and the others are off
  // Brightness values 205 - 409 light up LEDs 0-3 and the others are off
  // Brightness values 0 - 204 light up LEDs 0-4
  
  int led0Brightness = 0;
  int led1Brightness = 0;
  int led2Brightness = 0;
  int led3Brightness = 0;
  int led4Brightness = 0;
  
  if (brightness >= 820 && brightness <= 1023) {
    led0Brightness = (int)((float)brightness * 1.25);
  } else if (brightness >= 615 && brightness <= 819) {
    led0Brightness = 255;
    led1Brightness = (int)((float)(brightness - 205) * 1.25);
  } else if (brightness >= 410 && brightness <= 614) {
    led0Brightness = led1Brightness = 255;
    led2Brightness = (int)((float)(brightness - 410) * 1.25);
  } else if (brightness >= 205 && brightness <= 409) {
    led0Brightness = led1Brightness = led2Brightness = 255;
    led3Brightness = (int)((float)(brightness - 615) * 1.25);
  } else if (brightness <= 204) {
    led0Brightness = led1Brightness = led2Brightness = led3Brightness = 255;
    led4Brightness = (int)((float)(brightness - 820) * 1.25);
  }
  

  Serial.println(led0Brightness);
  Serial.println(led1Brightness);
  Serial.println(led2Brightness);
  Serial.println(led3Brightness);
  Serial.println(led4Brightness);
  
  analogWrite(LED_ARRAY_ELEMENT_0, led0Brightness);
  analogWrite(LED_ARRAY_ELEMENT_1, led1Brightness);
  analogWrite(LED_ARRAY_ELEMENT_2, led2Brightness);
  analogWrite(LED_ARRAY_ELEMENT_3, led3Brightness);
  analogWrite(LED_ARRAY_ELEMENT_4, led4Brightness);
}
