#include <Adafruit_NeoPixel.h>

// Three Buttons
#define BUTTON_ONE_PIN 8
#define BUTTON_TWO_PIN 10
#define BUTTON_THREE_PIN 12

// NeoPixel Strip Information
#define PRIMARY_PIN 5
#define NUM_PIXEL 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXEL, PRIMARY_PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.show();

  // Set 'read' pins to INPUT
  pinMode(BUTTON_ONE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_TWO_PIN, INPUT_PULLUP);
  pinMode(BUTTON_THREE_PIN, INPUT_PULLUP);
  
}

void loop() {
  bool buttonOnePinValue = digitalRead(BUTTON_ONE_PIN);
  bool buttonTwoPinValue = digitalRead(BUTTON_TWO_PIN);
  bool buttonThreePinValue = digitalRead(BUTTON_THREE_PIN);

  Serial.println("B1: " + String(buttonOnePinValue) + " B2:" + String(buttonTwoPinValue) + " B3: " + String(buttonThreePinValue));

  if (buttonOnePinValue == LOW && buttonTwoPinValue == HIGH && buttonThreePinValue == HIGH) {
    Serial.println("Turn the Strip Purple");
    turnLEDStripPurple();
  } else if (buttonTwoPinValue == LOW && buttonOnePinValue == HIGH && buttonThreePinValue == HIGH) {
    Serial.println("Turn the Strip Green");
    turnLEDStripGreen();
  } else if (buttonThreePinValue == LOW && buttonOnePinValue == HIGH && buttonTwoPinValue == HIGH) {
    Serial.println("Turn the Strip Blue");
    turnLEDStripBlue();
  } else if (buttonOnePinValue == LOW && buttonTwoPinValue == HIGH && buttonThreePinValue == LOW) {
    Serial.println("Turn the Strip Red");
    turnLEDStripRed();
  } else if (buttonOnePinValue == LOW && buttonTwoPinValue == LOW && buttonThreePinValue == LOW) {
    Serial.println("Turn the Strip Rainbow");
    turnLEDStripRainbow();
  } else {
    Serial.println("Turn the Strip Off");
    turnLEDStripOff();
  }

  delay(500);
}

void turnLEDStripOff() {
  setStripToSingleColor(0x00, 0x00, 0x00);
}

void turnLEDStripPurple() {
  setStripToSingleColor(0xFF, 0x00, 0xFF);
}

void turnLEDStripGreen() {
  setStripToSingleColor(0x00, 0xFF, 0x00);
}

void turnLEDStripRed() {
  setStripToSingleColor(0xFF, 0x00, 0x00);
}

void turnLEDStripBlue() {
  setStripToSingleColor(0x00, 0x00, 0xFF);
}

void turnLEDStripRainbow() {
  strip.setPixelColor(0, 0xFF, 0x00, 0x00); // R
  strip.setPixelColor(1, 0xFF, 0x88, 0x0E); // O
  strip.setPixelColor(2, 0xF2, 0xF4, 0x0A); // Y

  strip.setPixelColor(3, 0x00, 0xFF, 0x00); // G

  strip.setPixelColor(4, 0x00, 0x00, 0xFF); // B
  strip.setPixelColor(5, 0x41, 0x0A, 0xF4); // I
  strip.setPixelColor(6, 0xFF, 0x00, 0xFF); // V

  strip.show();
}

void setStripToSingleColor(byte r, byte g, byte b) {
  for (int i = 0; i < NUM_PIXEL; i++) {
    strip.setPixelColor(i, r, g, b);
  }

  strip.show();
}

