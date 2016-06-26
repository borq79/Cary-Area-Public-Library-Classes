#include "simon.h"

int sequenceCounter = 0;
uint8_t sequence[MAX_SEQUENCE];

void setup() 
{
  Serial.begin(9600);
  
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(BUTTON_ONE, INPUT_PULLUP);
  pinMode(BUTTON_TWO, INPUT_PULLUP);
  pinMode(BUTTON_THREE, INPUT_PULLUP);

  pinMode(LED_ONE, OUTPUT);
  pinMode(LED_TWO, OUTPUT);
  pinMode(LED_THREE, OUTPUT);

  restartGame();
  delay(2000);

  gameOver();
  
  gameWon();
}


void loop() 
{
  displaySequence();
  sequenceCounter++;
  
  if (readUserInput() == false) {
    gameOver();
    restartGame();  
  } else if (sequenceCounter == MAX_SEQUENCE) {
    gameWon();
  }
}

void restartGame() {
  generateSequence();
  sequenceCounter = 0;
  playMusic(theme);
}

void generateSequence() {
  randomSeed(analogRead(0));

  Serial.println("Sequence ...");
  for(int i = 0; i < MAX_SEQUENCE; i++) {
    uint8_t randNumber = (uint8_t)random(1, 4);
    sequence[i] = randNumber;
    Serial.print(sequence[i]); Serial.print(",");
  }
  Serial.println("");

  sequenceCounter = 0;
}

void displaySequence() {
  for(int i = 0; i <= sequenceCounter; i++) {
    uint8_t sequenceValue = sequence[i];

    Serial.print("Sequence Value: "); Serial.println(sequenceValue);

    int ledPin = sequenceValue == 1 ? LED_ONE : (sequenceValue == 2 ? LED_TWO : LED_THREE);
    int noteToPlay = ledPin == LED_ONE ? 294 : (ledPin == LED_TWO ? 392 : (ledPin == LED_THREE ? 523 : 0));

    Serial.print("Note: "); Serial.println(noteToPlay);
    Serial.print("LED: "); Serial.println(ledPin);

    digitalWrite(ledPin, HIGH);
    tone(BUZZER_PIN, noteToPlay, 500);

    delay(500);

    digitalWrite(LED_ONE, LOW);
    digitalWrite(LED_TWO, LOW);
    digitalWrite(LED_THREE, LOW);
  }
    
}

void gameOver() {
  playMusic(gameover);
  
  // Super Mario Brothers Game Over
  /*tone(BUZZER_PIN, 523, 600); // C
  tone(BUZZER_PIN, 494, 600); // G
  tone(BUZZER_PIN, 440, 900); // E

  tone(BUZZER_PIN, 494, 600); // B
  tone(BUZZER_PIN, 440, 600); // A
  tone(BUZZER_PIN, 494, 900); // B
  tone(BUZZER_PIN, 440, 900); // A
  tone(BUZZER_PIN, 494, 900); // B
  tone(BUZZER_PIN, 440, 900); // A

  tone(BUZZER_PIN, 392, 300); // G
  tone(BUZZER_PIN, 349, 300); // F
  tone(BUZZER_PIN, 330, 2000); // E*/

  // Ending Lights

  delay(5000);
}

void gameWon() {
  // End song
  playMusic(flagpole);
  
  // End lights

  delay(5000);
}

bool readUserInput() {
  int sequenceRemembered = true;
  
  int numberOfUserButtonPresses = 0;
  int expectedUserButtonPresses = sequenceCounter;

  while (numberOfUserButtonPresses < expectedUserButtonPresses) {
    int buttonOneValue = digitalRead(BUTTON_ONE);
    int buttonTwoValue = digitalRead(BUTTON_TWO);
    int buttonThreeValue = digitalRead(BUTTON_THREE);

    int buttonPressed = (buttonOneValue == LOW ? 1 : (buttonTwoValue == LOW ? 2 : (buttonThreeValue == LOW ? 3 : 0)));
    if (buttonPressed > 0) {
      if (sequence[numberOfUserButtonPresses] != buttonPressed) {
        sequenceRemembered = false;
        break;
      }

      numberOfUserButtonPresses++;
    }
  }

  return sequenceRemembered;


 /* Serial.print("Button 1: "); Serial.println(buttonOneValue);
  Serial.print("Button 2: "); Serial.println(buttonTwoValue);
  Serial.print("Button 3: "); Serial.println(buttonThreeValue); */

  

}


// Borrowed these note arrays from https://github.com/tsukisan/Arduino/tree/master/WiiClassicSoundboard
void playMusic(const int *song) {
  if (song != NULL) {
    int numberOfNotes = song[0];
    
    //Serial.print("# Notes: "); Serial.println(numberOfNotes);

    for(int i = 1; i < (numberOfNotes * 2); i += 2) {
      int note =  song[i];
      int duration = song[i + 1];

      Serial.print("Note: "); Serial.println(note);
      Serial.print("Duration: "); Serial.println(duration);

      int durationMs = 1000 / duration;
      
      tone(BUZZER_PIN, note, durationMs);
      delay(durationMs * 1.30);
      noTone(BUZZER_PIN); 
    }
  }
}

