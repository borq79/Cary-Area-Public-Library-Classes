#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
#include <Twitter.h>

// Twitter allows 140 characters
#define MAX_TWITTER_MESSAGE 140

// The buffer that needs to hold the message needs an extra byte to store the NULL character
#define TWITTER_MESSAGE_BUFFER_SIZE (MAX_TWITTER_MESSAGE + 1)

// Digital pin that the DHT11 is connected to
#define DHT11PIN 2

// Init the DHT11 Library
DHT dht(DHT11PIN, DHT11);

// Set to false to read in Celsius, true to read in Fahrenheit
#define READ_IN_FAHRENHEIT true

// Delay time for twitter library to avoid overwhelming the server
#define ONE_MINUTE 60000

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Fallback, static IP, in case DHCP fails
IPAddress ip(192, 168, 0, 12);  

Twitter twitter("PUT YOUR TWITTER TOKEN KEY HERE");

// Structure used to store ambient readings
struct AMBIENT {
  float temperature;
  float humidity;
};

// Function prototypes
AMBIENT getAmbientReadings();
void sendReadingsToTwitter(AMBIENT &readings);


void setup() {
  // Init the serial communications for debugging messages
  Serial.begin(9600);
  
  // Attempt to get an IP. If it fails, bind a static IP
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP. Going to attempt and bind the fallback static IP");
    Ethernet.begin(mac, ip);
  }
  
  // Intialize the DHT11 sensor
  dht.begin();
}

void loop() {
  AMBIENT readings = getAmbientReadings();
  sendReadingsToTwitter(readings);

  Serial.println("Waiting one minute before getting the next reading ...");
  delay(ONE_MINUTE);

}
 
AMBIENT getAmbientReadings() {
  AMBIENT readings;
  
  readings.humidity = dht.readHumidity();
  readings.temperature = dht.readTemperature(READ_IN_FAHRENHEIT);

  return readings;
}

void sendReadingsToTwitter(AMBIENT &readings) {
  char twitterMessage[TWITTER_MESSAGE_BUFFER_SIZE];
  char temperatureString[10];
  char humidityString[10];
  
  // Convert the temperature and humidity to strings so they can be printed
  dtostrf(readings.temperature, 4, 2, temperatureString);
  dtostrf(readings.humidity, 4, 2, humidityString);
  
  // Create the twitter message - it will crop it to 140 characters (MAX_TWITTER_MESSAGE) and ensure the NULL is in place (why we add 1 to get TWITTER_MESSAGE_BUFFER_SIZE)
  snprintf(twitterMessage, TWITTER_MESSAGE_BUFFER_SIZE, "The Cary Area Public Library is currently %s degrees Fahrenheit with a humidity of %s%%", temperatureString, humidityString);
  
  // Print for our own sake
  Serial.println(twitterMessage);

  Serial.println("Connecting to the Twitter Arduino proxy ...");
  if (twitter.post(twitterMessage)) {
    int status = twitter.wait();
    if (status == 200) {
      Serial.println("Success.");
    } else {
      Serial.print("Failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("The connection to the Twitter Arduino proxy failed.");
  }

}

