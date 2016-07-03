#include <Adafruit_NeoPixel.h>
#include "simon.h"


const int BUTTONS[] = { BUTTON_ONE_PIN, BUTTON_TWO_PIN, BUTTON_THREE_PIN, BUTTON_FOUR_PIN };

Adafruit_NeoPixel strip = Adafruit_NeoPixel(SIZE_OF_NEO_PIXEL_BAR, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  // Initialize the new pixel strip library
  strip.begin();

  // Initialize all pixels to 'off'
  strip.show();

  // So we can debug ... if needed
  Serial.begin(9600);

  // Initialize the buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // The four buttons need pullup resistors so we can tell when the button is pressed
  // Otherwise it falls back to high impedance 
  for(int i =0 ; i < NUM_BUTTONS; i++) {
    pinMode(BUTTONS[i], INPUT_PULLUP);
  }
}

void loop() 
{
  playMusic(theme);
  delay(1500);
  
  playMusic(gameover);
  delay(2000);

  playMusic(flagpole);
  delay(5000);
}

// Borrowed these note arrays from https://github.com/tsukisan/Arduino/tree/master/WiiClassicSoundboard
void playMusic(const int *song) {
  if (song != NULL) {
    int numberOfNotes = song[0];
    
    for(int i = 1; i < (numberOfNotes * 2); i += 2) {
      int note =  song[i];
      int duration = song[i + 1];

      int durationMs = 1000 / duration;
      
      tone(BUZZER_PIN, note, durationMs);
      delay(durationMs * 1.30);
      noTone(BUZZER_PIN); 
    }
  }
}
