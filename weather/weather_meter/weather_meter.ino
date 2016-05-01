#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Temboo.h>

// NeoPixel Strip Information
#define PRIMARY_PIN 5
#define NUM_PIXEL 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXEL, PRIMARY_PIN, NEO_GRB + NEO_KHZ800);

// Temboo Account Infomration
#define TEMBOO_ACCOUNT ""  // Your Temboo account name 
#define TEMBOO_APP_KEY_NAME ""  // Your Temboo app key name
#define TEMBOO_APP_KEY ""  // Your Temboo app key

// Ethernet Shield Information
#define ETHERNET_SHIELD_MAC {0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x00}
byte ethernetMACAddress[] = ETHERNET_SHIELD_MAC;
EthernetClient client;

// A way to pass around information about the conditions and what the LEDs should reflect
struct CONDITION_INFO {
  byte r;
  byte g;
  byte b;
  bool isEmergency;
};

// Weather Conditions to Color Mapping      
#define SEVERE_WEATHER (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define STORMY         (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define WINTER_MIX     (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define SUNNY          (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define CLOUDY         (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define RAIN           (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define WINDY          (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define HAIL           (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define LOW_VISIBILITY (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define FAIR_DAY       (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define FAIR_NIGHT     (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define HOT            (CONDITION_INFO){0xFF, 0x00, 0x00, true}
#define COLD           (CONDITION_INFO){0xFF, 0x00, 0x00, true}

// ***********************************************************
// * Function Prototypes
// ***********************************************************
void displayCondition(CONDITION_INFO &condition);
CONDITION_INFO getColorFromCondition(int condition);


// ***********************************************************
// * Setup
// ***********************************************************
void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.show();

  // For debugging, wait until the serial console is connected
  delay(4000);
  while (!Serial);

  Serial.print("DHCP:");
  if (Ethernet.begin(ethernetMACAddress) == 0) {
    Serial.println("FAIL");
    while (true);
  }
  Serial.println("OK");
  delay(5000);

  //print out the IP address
  Serial.print("IP = ");
  Serial.println(Ethernet.localIP());

  Serial.println("Setup complete.\n");
}

// ***********************************************************
// * Main Application Loop
// ***********************************************************
void loop() {
  Serial.println("Running GetWeatherByAddress");

  TembooChoreo GetWeatherByAddressChoreo(client);

  // Invoke the Temboo client
  GetWeatherByAddressChoreo.begin();

  // Set Temboo account credentials
  GetWeatherByAddressChoreo.setAccountName(TEMBOO_ACCOUNT);
  GetWeatherByAddressChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  GetWeatherByAddressChoreo.setAppKey(TEMBOO_APP_KEY);

  // Set Choreo inputs
  String AddressValue = "60013";
  GetWeatherByAddressChoreo.addInput("Address", AddressValue);

  // Identify the Choreo to run
  GetWeatherByAddressChoreo.setChoreo("/Library/Yahoo/Weather/GetWeatherByAddress");

  // Run the Choreo
  unsigned int returnCode = GetWeatherByAddressChoreo.run();
  Serial.print("Return Code: "); Serial.println(returnCode);

  // A return code of zero means everything worked
  if (returnCode == 0) {
    while (GetWeatherByAddressChoreo.available()) {
      String name = GetWeatherByAddressChoreo.readStringUntil('\x1F');
      name.trim();

      String data = GetWeatherByAddressChoreo.readStringUntil('\x1E');
      data.trim();

      if (name == "ConditionCode") {
        Serial.println("Condition Code: " + String(data.toInt()));

        CONDITION_INFO conditionInfo = getColorFromCondition(data.toInt());
        displayCondition(conditionInfo);
      } else if (name == "ConditionText") {
        Serial.println("Condition Text: " + data);
      }
    }
  }

  GetWeatherByAddressChoreo.close();

  Serial.println("\nWaiting...\n");
  delay(1800000); // wait 30 minutes between GetWeatherByAddress calls
}

void displayCondition(CONDITION_INFO &condition) {
  Serial.println("Setting R, G, B to: " + String(condition.r) + ", " + String(condition.g) + ", " + String(condition.b));
  for (int i = 0; i < NUM_PIXEL; i++) {
    strip.setPixelColor(i, condition.r, condition.b, condition.g);
  }

  strip.show();
}

CONDITION_INFO getColorFromCondition(int condition) {
  CONDITION_INFO conditionInfo;

  switch (condition) {

    // tornado
    case 0:
      conditionInfo = SEVERE_WEATHER;
      break;

    // tropical storm
    case 1:
      conditionInfo = SEVERE_WEATHER;
      break;

    // hurricane
    case 2:
      conditionInfo = SEVERE_WEATHER;
      break;

    // severe thunderstorms
    case 3:
      conditionInfo = SEVERE_WEATHER;
      break;

    // thunderstorms
    case 4:
      conditionInfo = STORMY;
      break;

    // mixed rain and snow
    case 5:
      conditionInfo = WINTER_MIX;
      break;

    // mixed rain and sleet
    case 6:
      conditionInfo = WINTER_MIX;
      break;

    // mixed snow and sleet
    case 7:
      conditionInfo = WINTER_MIX;
      break;

    // freezing drizzle
    case 8:
      conditionInfo = WINTER_MIX;
      break;

    // drizzle
    case 9:
      conditionInfo = RAIN;
      break;

    // freezing rain
    case 10:
      conditionInfo = WINTER_MIX;
      break;

    // showers
    case 11:
      conditionInfo = RAIN;
      break;

    // showers
    case 12:
      conditionInfo = RAIN;
      break;

    // snow flurries
    case 13:
      conditionInfo = WINTER_MIX;
      break;

    // light snow showers
    case 14:
      conditionInfo = WINTER_MIX;
      break;

    // blowing snow
    case 15:
      conditionInfo = WINTER_MIX;
      break;

    // snow
    case 16:
      conditionInfo = WINTER_MIX;
      break;

    // hail
    case 17:
      conditionInfo = HAIL;
      break;

    // sleet
    case 18:
      conditionInfo = WINTER_MIX;
      break;

    // dust
    case 19:
      conditionInfo = LOW_VISIBILITY;
      break;

    // foggy
    case 20:
      conditionInfo = LOW_VISIBILITY;
      break;

    // haze
    case 21:
      conditionInfo = LOW_VISIBILITY;
      break;

    // smoky
    case 22:
      conditionInfo = LOW_VISIBILITY;
      break;

    // blustery
    case 23:
      conditionInfo = WINDY;
      break;

    // windy
    case 24:
      conditionInfo = WINDY;
      break;

    // cold
    case 25:
      conditionInfo = COLD;
      break;

    // cloudy
    case 26:
      conditionInfo = CLOUDY;
      break;

    // mostly cloudy (night)
    case 27:
      conditionInfo = CLOUDY;
      break;

    // mostly cloudy (day)
    case 28:
      conditionInfo = CLOUDY;
      break;

    // partly cloudy (night)
    case 29:
      conditionInfo = CLOUDY;
      break;

    // partly cloudy (day)
    case 30:
      conditionInfo = CLOUDY;
      break;

    // clear (night)
    case 31:
      conditionInfo = CLOUDY;
      break;

    // sunny
    case 32:
      conditionInfo = SUNNY;
      break;

    // fair (night)
    case 33:
      conditionInfo = FAIR_NIGHT;
      break;

    // fair (day)
    case 34:
      conditionInfo = FAIR_DAY;
      break;

    // mixed rain and hail
    case 35:
      conditionInfo = HAIL;
      break;

    // hot
    case 36:
      conditionInfo = HOT;
      break;

    // isolated thunderstorms
    case 37:
      conditionInfo = STORMY;
      break;

    // scattered thunderstorms
    case 38:
      conditionInfo = STORMY;
      break;

    // scattered thunderstorms
    case 39:
      conditionInfo = STORMY;
      break;

    // scattered showers
    case 40:
      conditionInfo = RAIN;
      break;

    // heavy snow
    case 41:
      conditionInfo = WINTER_MIX;
      break;

    // scattered snow showers
    case 42:
      conditionInfo = WINTER_MIX;
      break;

    // heavy snow
    case 43:
      conditionInfo = WINTER_MIX;
      break;

    // partly cloudy
    case 44:
      conditionInfo = CLOUDY;
      break;

    // thundershowers
    case 45:
      conditionInfo = STORMY;
      break;

    // snow showers
    case 46:
      conditionInfo = WINTER_MIX;
      break;

    // isolated thundershowers
    case 47:
      conditionInfo = STORMY;
      break;

    // not available
    case 3200:
      conditionInfo = (CONDITION_INFO) {
        0xFF, 0xFF, 0xFF, false
      };
      break;
  }

  return conditionInfo;
}


