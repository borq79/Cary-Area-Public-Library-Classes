#include <Adafruit_NeoPixel.h>


#define PRIMARY_PIN 5
#define NUM_PIXEL 8

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXEL, PRIMARY_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  // Initialize the strip library
  strip.begin();

  // Initialize all pixels to 'off'
  strip.show();

  // Set the strip to a rainbow - ROY G BIV + White - according to the CSS colors http://colrd.com/palette/23813/?download=css
  strip.setPixelColor(0, 209, 0, 0);
  strip.setPixelColor(1, 255, 102, 34);
  strip.setPixelColor(2, 255, 218, 33);
  strip.setPixelColor(3, 51, 221, 0);
  strip.setPixelColor(4, 17, 51, 204);
  strip.setPixelColor(5, 17, 51, 204);
  strip.setPixelColor(6, 51, 0, 68);
  strip.setPixelColor(7, 255, 255, 255);

  // refresh the pixels
  strip.show();

  // To debug via the console if need be
  Serial.begin(9600);
}

void loop() {
}

