//This code is designed to be used with good old LEDs, connected in parallel to the PWM channels and common ground
//Author: Daniel Gorbunov

const int StrobePin = 22;
const int ResetPin = 24;
const int DataIn = A15;

const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

int spectrum[7];
int smoothed[7];

// ADJUSTMENT //
const int noisethresh = 15; //process data to cut off anything below this, i.e. noise
const int smoothing = 6; //how many times we smooth out the spectrum data. More smoothing = less transients

void setup() {
  Serial.begin(9600);
  
  pinMode(StrobePin, OUTPUT);
  pinMode(ResetPin, OUTPUT);
  digitalWrite(StrobePin, HIGH);
  digitalWrite(ResetPin, LOW);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

}

void loop() {
  readData();
  smoothData();
  for (int i=0; i<7; i++)
  {
    if (spectrum[i] < 100) Serial.print(" ");
    if (spectrum[i] < 10) Serial.print(" ");
    Serial.print(spectrum[i]);
    Serial.print(" ");
  }
  Serial.println();

    analogWrite(led1, processData(spectrum[0]));
    //analogWrite(led2, processData(spectrum[1]));
    analogWrite(led3, processData(spectrum[2]));
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

void smoothData(){
  for (int i = 0 ; i <7; i++){
     int total = 0;
  for (int n = 0 ; n <=smoothing; n++){
    total = total + spectrum[i];
  }
    smoothed[i] = total/smoothing;
  }
}


int processData(int input) {
  
 int x = input - noisethresh;
 input = max(x, 0);
 //input = pow(1.2*input,1.3);
 return input;
}

