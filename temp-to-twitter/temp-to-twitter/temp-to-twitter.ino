#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
#include <Twitter.h>

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

Twitter twitter("<<< your token here >>>");


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
  
  readings.temperature = dht.readHumidity();
  readings.humidity = dht.readTemperature(READ_IN_FAHRENHEIT);
}

void sendReadingsToTwitter(AMBIENT &readings) {
  String twitterMessage = "Current Reading in the Library: The temperature is ";
  twitterMessage.concat(readings.temperature);
  twitterMessage += " degrees Fahrenheit and the humidity is ";
  twitterMessage.concat(readings.humidity);
  twitterMessage += "%";
  Serial.println(twitterMessage.c_str());

  Serial.println("Connecting to the Twitter Arduino proxy ...");
  if (twitter.post(twitterMessage.c_str())) {
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

