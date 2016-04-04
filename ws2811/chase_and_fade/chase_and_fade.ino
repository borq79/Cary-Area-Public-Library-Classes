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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXEL, PRIMARY_PIN, NEO_GRB + NEO_KHZ800);

// 32-bit colors to cycle through
static const uint32_t colors[] = { 0x00FF0000, 0x0000FF00, 0x000000FF, 0x00FF00FF, 0x00FFFF00, 0x0000FFFF };

// The number of colors to cycle through
static const uint32_t numOfColors = sizeof(colors) / sizeof(uint32_t);

void setup() {
  // Initialize the strip library
  strip.begin();

  // Initialize all pixels to 'off'
  strip.show();

  // To debug via the console if need be
  Serial.begin(9600);
}
void loop() {
  chase();
  fade();
}


void chase() {
  for(int colorIndex = 0; colorIndex < numOfColors; colorIndex++) {
    for(int pixelIndex = 0; pixelIndex < NUM_PIXEL; pixelIndex++ ) {
      strip.setPixelColor(pixelIndex, colors[colorIndex]);
      strip.show();
      delay(200);
    }
  }
}

void fade() {
  for(uint32_t colorIndex = 0; colorIndex < numOfColors; colorIndex++) {
    for(uint32_t brightness = 0; brightness < 255; brightness += 8) {
      uint32_t brightness32Bit = (brightness & 0x0000FF) | ((brightness << 8) & 0x00FF00) | ((brightness << 16) & 0xFF0000);  
      uint32_t mixedColor = colors[colorIndex] & brightness32Bit; 
        
      for(uint32_t pixelIndex = 0; pixelIndex < NUM_PIXEL; pixelIndex++ ) {
        strip.setPixelColor(pixelIndex, mixedColor);
      }
      
      strip.show();
      delay(50);
    }
  }
}

