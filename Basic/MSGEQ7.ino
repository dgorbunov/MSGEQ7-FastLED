#include <FastLED.h>

#define NUM_LEDS 150

#define DATA_PIN 7

CRGB leds[NUM_LEDS];

int StrobePin = 22;
int ResetPin = 24;
const int DataIn = A15;

int spectrum[7];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  
  pinMode(StrobePin, OUTPUT);
  pinMode(ResetPin, OUTPUT);
  digitalWrite(StrobePin, HIGH);
  digitalWrite(ResetPin, LOW);

  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  readData();

  for (int i=0; i<7; i++)
  {
    if (spectrum[i] < 100) Serial.print(" ");
    if (spectrum[i] < 10) Serial.print(" ");
    Serial.print(spectrum[i]);
    Serial.print(" ");
  }
  Serial.println();

  for (int n=0; n<7; n++) {

  for(int i = 0; i < round(spectrum[n]/7.5); i++) {
    // set our current dot to red, green, and blue
    leds[i] = spectrum[n];
    FastLED.show();
  }
  }

  if (spectrum[0]> 175) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else{
    digitalWrite(LED_BUILTIN, LOW);
  }
  
}




void readData() {
  digitalWrite(ResetPin, HIGH);
  digitalWrite(ResetPin, LOW);
  delayMicroseconds(75);

  for (int i = 0 ; i <7; i++)
  {
    digitalWrite(StrobePin, LOW);
    delayMicroseconds(40);

    spectrum[i] = analogRead(DataIn) / 4;

    digitalWrite(StrobePin, HIGH);
    delayMicroseconds(40);
  }
}
