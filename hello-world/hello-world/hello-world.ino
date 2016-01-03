#define DELAY_TIME_MS 3000 // Delay 3 seconds (3000ms)

uint32_t loopCounter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.println("This is the setup function that will run only once at the start of the execution");
}

void loop() {
  // Print to the serial/USB output
  Serial.println("Staring at the top of the main application loop ...");

  // Just wait some time to slow things down
  delay(DELAY_TIME_MS);

  // Increment the loop counter
  loopCounter++;

  // Indicate how many times the loop has run
  Serial.print("The loop has looped "); Serial.print(loopCounter); Serial.println(" times.");
}
