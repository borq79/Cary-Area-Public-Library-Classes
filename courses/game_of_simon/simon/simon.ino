/*
  note 	frequency
  c     262 Hz
  d     294 Hz
  e     330 Hz
  f     349 Hz
  g     392 Hz
  a     440 Hz
  b     494 Hz
  C     523 Hz

For more information, see http://arduino.cc/en/Tutorial/Tone
*/
  
#define BUZZER_PIN   11
#define BUTTON_ONE   2
#define BUTTON_TWO   4
#define BUTTON_THREE 6
#define LED_ONE      8
#define LED_TWO      9
#define LED_THREE    10


#define MAX_SEQUENCE 15

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

  generateSequence();
}


void loop() 
{
  int buttonOneValue = digitalRead(BUTTON_ONE);
  int buttonTwoValue = digitalRead(BUTTON_TWO);
  int buttonThreeValue = digitalRead(BUTTON_THREE);

 /* Serial.print("Button 1: "); Serial.println(buttonOneValue);
  Serial.print("Button 2: "); Serial.println(buttonTwoValue);
  Serial.print("Button 3: "); Serial.println(buttonThreeValue);


  digitalWrite(LED_ONE, buttonOneValue == LOW ? HIGH : LOW);
  digitalWrite(LED_TWO, buttonTwoValue == LOW ? HIGH : LOW);
  digitalWrite(LED_THREE, buttonThreeValue == LOW ? HIGH : LOW);

  int noteToPlay = buttonOneValue == LOW ? 294 : (buttonTwoValue == LOW ? 392 : (buttonThreeValue == LOW ? 523 : 0));
  tone(BUZZER_PIN, noteToPlay, 2000);

  delay(50);*/


  displaySequence();
  delay(2000);
  sequenceCounter++;

  displaySequence();
  delay(2000);
  sequenceCounter++;

  displaySequence();
  delay(2000);
  sequenceCounter++;
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

void readUserInput() {
  
}

