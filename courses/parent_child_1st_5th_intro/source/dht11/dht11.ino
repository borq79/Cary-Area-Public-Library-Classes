#include <DHT.h>


// Max size of message
#define MAX_MESSAGE_SIZE 256

// Digital pin that the DHT11 is connected to
#define DHT11PIN 13

// Init the DHT11 Library
DHT dht(DHT11PIN, DHT11);

// Set to false to read in Celsius, true to read in Fahrenheit
#define READ_IN_FAHRENHEIT true

// Structure used to store ambient readings
struct AMBIENT {
  float temperature;
  float humidity;
};

// Function prototypes
AMBIENT getAmbientReadings();
void printReadings(AMBIENT &readings);

void setup() {
  // Init the serial communications for debugging messages
  Serial.begin(9600);
  
  // Intialize the DHT11 sensor
  dht.begin();
}

void loop() {
  AMBIENT readings = getAmbientReadings();
  printReadings(readings);
  
  Serial.println("Waiting 5 seconds before getting the next reading ...");
  delay(5000);

}
 
AMBIENT getAmbientReadings() {
  AMBIENT readings;
  
  readings.humidity = dht.readHumidity();
  readings.temperature = dht.readTemperature(READ_IN_FAHRENHEIT);

  return readings;
}

void printReadings(AMBIENT &readings) {
  char message[MAX_MESSAGE_SIZE];
  char temperatureString[10];
  char humidityString[10];
  
  // Convert the temperature and humidity to strings so they can be printed
  dtostrf(readings.temperature, 4, 2, temperatureString);
  dtostrf(readings.humidity, 4, 2, humidityString);
  
  // Create the message - it will crop it to MAX_MESSAGE_SIZE - 1 characters and ensure the NULL is in place
  snprintf(message, MAX_MESSAGE_SIZE, "The Cary Area Public Library is currently %s degrees Fahrenheit with a humidity of %s%%", temperatureString, humidityString);
  
  // Print for our own sake
  Serial.println(message);
}

