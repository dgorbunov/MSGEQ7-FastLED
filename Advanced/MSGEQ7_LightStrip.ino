//This versiono of the code is designed to be used in conjunction with addressable light strips (I'm using a WS2182B one), but this can be easily configured for any particular strip.
//Author: Daniel Gorbunov

#include <FastLED.h>

#define NUM_LEDS 150

#define DATA_PIN 7

CRGB leds[NUM_LEDS];

const int StrobePin = 22;
const int ResetPin = 24;
const int DataIn = A15;

const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

int spectrum[7];
int processed[7];
int smoothed[7];
int index;

// ADJUSTMENT //
const int noisethresh = 25; //process data to cut off anything below this, i.e. noise
const int samples = 5; //number of samples to take before 
const bool median = false; //if set to false mean will be used

int total[samples][7]; //2D array for smoothing data

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  
  pinMode(StrobePin, OUTPUT);
  pinMode(ResetPin, OUTPUT);
  digitalWrite(StrobePin, HIGH);
  digitalWrite(ResetPin, LOW);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

}

void loop() {
  for (index=0; index < samples; index++) readData();

  
//Comment out for debugging purposes
//  for (int i=0; i<7; i++)
//    {
//    Serial.print(spectrum[i]);
//    Serial.print(" ");
//    }
//  Serial.println();
  
  runStrip();
 
  analogWrite(led1, smoothed[0]);
  analogWrite(led2, smoothed[1]);
  analogWrite(led3, smoothed[2]);
  
}


void readData() {
  
    digitalWrite(ResetPin, HIGH);
    digitalWrite(ResetPin, LOW);
    delayMicroseconds(75);
  
  for (int i = 0 ; i <7; i++) {
    digitalWrite(StrobePin, LOW);
    delayMicroseconds(40);

    spectrum[i] = analogRead(DataIn) / 4;

    digitalWrite(StrobePin, HIGH);
    delayMicroseconds(40);

    
    processData(spectrum[i], i, false);

  }
  processData(0, 0, true); //calculate!

}

void runStrip() {
for (int n = 0; n < 7; n++) {
  for(int i = 0; i < 21; i++) {
    
    leds[21*n + i].setRGB(smoothed[n], smoothed[n], smoothed[n]); //0 - kick 2 - clap 6 - hihat
    }

}

FastLED.show();
}
int processData(int input, int bin, bool calc) {
  memset(smoothed, 0, sizeof(smoothed)); //reset smoothed arra

if (calc) {
    if (median) {

    }
    else {
      for (bin =  0; bin < samples; bin++) {
      for (index = 0; index < samples; index++) {
        smoothed[bin] = smoothed[bin] + total[index][bin];
      }
        smoothed[bin] = smoothed[bin] / samples;
    }
  }

} else {
   processed[input] = input - noisethresh; //noisefloor
   processed[input] = max(processed[input], 0);  //limit to positive numbers
  
   total[index][bin] = processed[input];
   return processed[input];
    }
}




