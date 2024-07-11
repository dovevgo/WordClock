#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "PASSWOD";

// NTP server details
const long utcOffsetInSeconds = 10800; // (UTC+2)
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
#define NUM_LEDS 72
#define DATA_PIN 2
CRGB leds[NUM_LEDS];
CRGB colors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::White, CRGB::Orange};

const int IT_IS[3] = {71, 70, 69};
const int TEN_M[3] = {68, 67, 66};
const int HALF[3] = {65, 64, 63};
const int QUARTER[4] = {57, 56, 55, 54};
const int TWENTY[4] = {62, 61, 60, 59};
const int FIVE_M[3] = {53, 52, 51};
const int MINUTES[4] = {50, 49, 48, 47};
const int TO[2] = {45,46};
const int TWO[3] = {44, 43, 42};
const int ONE[3] = {40, 39,41};
const int PAST[3] = {38, 36, 37};
const int THREE[4] = {35, 34, 33, 32};
const int FOUR[2] = {31, 30};
const int FIVE[3] = {29, 28, 27};
const int EIGHT[3] = {26, 25, 24};
const int SEVEN[4] = {23, 22, 21, 20};
const int SIX[2] = {19, 18};
const int NINE[3] = {17, 16, 15};
const int TEN[2] = {14, 13};
const int ELEVEN[4] = {9, 10, 11, 12};
const int TWELVE[4] = {0, 1, 2, 3};
const int OCLOCK[4] = {5, 6, 7, 8};

unsigned long startTime;
unsigned long twelveHoursInMilliseconds = 43200000; // 12 hours in milliseconds


void lightSpecificLeds(const int* ledArray, int size, CRGB color) {
    for (int i = 0; i < size; i++) {
        leds[ledArray[i]] = color;
    }
    FastLED.show();
}

void lightLed(int index, CRGB color){
  leds[index] = color;
  FastLED.show();
}

void clearLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

CRGB getColor(){
    return colors[random(0, 6)];
}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
   startTime = millis();
    //FastLED.setBrightness(30);
for(int i = 0; i < NUM_LEDS; i++) {
    if (i % 3 == 0) {
      lightLed(i, CRGB::Red);
    } else if (i % 3 == 1) {
      lightLed(i, CRGB::Green);
    } else {
      lightLed(i, CRGB::Yellow);
    }
  }

  delay(750);
  
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  delay(5000);
  timeClient.begin();
  for(int i = 0; i < NUM_LEDS; i++) {
    lightLed(i, CRGB::Black);
  }
}

void loop() {
    // put your main code here, to run repeatedly:
  timeClient.update();
  int hour = timeClient.getHours();
  int minute = timeClient.getMinutes();
  Serial.print(hour);
  Serial.print(":");
  Serial.println(minute);

  clearLEDs(); // Clear the LEDs before setting new words
  lightSpecificLeds(IT_IS, 3, getColor());
  if (minute >= 0 && minute < 5) {
    lightSpecificLeds(OCLOCK, 4, getColor());
  } 

  
  if (minute > 35){
    if (hour != 23){
      hour++;
    } else {
      hour = 0;
    }
  }
    
  
  if (hour == 1 || hour == 13) {
    lightSpecificLeds(ONE, 3, getColor());
  } else if (hour == 2 || hour == 14) {
    lightSpecificLeds(TWO, 3, getColor());
  } else if (hour == 3 || hour == 15) {
    lightSpecificLeds(THREE, 4, getColor());
  } else if (hour == 4 || hour == 16) {
    lightSpecificLeds(FOUR, 2, getColor());
  } else if (hour == 5 || hour == 17) {
    lightSpecificLeds(FIVE, 3, getColor());
  } else if (hour == 6 || hour == 18) {
    lightSpecificLeds(SIX, 2, getColor());
  } else if (hour == 7 || hour == 19) {
    lightSpecificLeds(SEVEN, 4, getColor());
  } else if (hour == 8 || hour == 20) {
    lightSpecificLeds(EIGHT, 3, getColor());
  } else if (hour == 9 || hour == 21) {
    lightSpecificLeds(NINE, 3, getColor());
  } else if (hour == 10 || hour == 22) {
    lightSpecificLeds(TEN, 2, getColor());
  } else if (hour == 11 || hour == 23) {
    lightSpecificLeds(ELEVEN, 4, getColor());
  } else if (hour == 12 || hour == 0) {
    lightSpecificLeds(TWELVE, 4, getColor());
  }
  // ... handle other hours

  // Handle minutes (you'll need to write similar logic for each five-minute increment)
  if (minute >= 5 && minute < 10) {
    lightSpecificLeds(FIVE_M, 2, getColor());
    lightSpecificLeds(MINUTES, 4,getColor());
    lightSpecificLeds(PAST, 3, getColor());
    
  }
  if (minute >= 10 && minute < 15) {
    lightSpecificLeds(TEN_M, 2, getColor());
    lightSpecificLeds(MINUTES, 4, getColor());
    lightSpecificLeds(PAST, 3, getColor());
  }
  if (minute >= 15 && minute < 20) {
    lightSpecificLeds(QUARTER, 4, getColor());
    lightSpecificLeds(PAST, 3, getColor());
  }
  if (minute >= 20 && minute < 25) {
    lightSpecificLeds(TWENTY, 4, getColor());
    lightSpecificLeds(MINUTES, 4, getColor());
    lightSpecificLeds(PAST, 3, getColor());
  }
  if (minute >= 25 && minute < 30) {
    lightSpecificLeds(TWENTY, 4, getColor());
    lightSpecificLeds(FIVE_M, 2, getColor());
    lightSpecificLeds(MINUTES, 4, getColor());
    lightSpecificLeds(PAST, 3, getColor());
  }
  if (minute >= 30 && minute < 35) {
    lightSpecificLeds(HALF, 3, getColor());
    lightSpecificLeds(PAST, 3, getColor());
  }
  if (minute >= 35 && minute < 40) {
    lightSpecificLeds(TWENTY, 4, getColor());
    lightSpecificLeds(FIVE_M, 2, getColor());
    lightSpecificLeds(MINUTES, 4, getColor());
    lightSpecificLeds(TO, 2, getColor());
  }
  if (minute >= 40 && minute < 45) {
    lightSpecificLeds(TWENTY, 4, getColor());
    lightSpecificLeds(MINUTES, 4, getColor());
    lightSpecificLeds(TO, 2, getColor());
  }
  if (minute >= 45 && minute < 50) {
    lightSpecificLeds(QUARTER, 4, getColor());
    lightSpecificLeds(TO, 2, getColor());
  }
  if (minute >= 50 && minute < 55) {
    lightSpecificLeds(TEN_M, 2, getColor());
    lightSpecificLeds(MINUTES, 4, getColor());
    lightSpecificLeds(TO, 2, getColor());
  }
  if (minute >= 55 ) {
    lightSpecificLeds(FIVE_M, 2, getColor());
    lightSpecificLeds(MINUTES, 4,getColor());
    lightSpecificLeds(TO, 2, getColor());
  }

  delay(60000);
  if (millis() - startTime >= twelveHoursInMilliseconds) {
    ESP.restart();
  }
}
