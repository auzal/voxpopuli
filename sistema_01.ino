#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>


SoftwareSerial mySerial(9, 11); // RX, TX
DFPlayerMini_Fast myDFPlayer;

const int number_of_songs = 25;

const int ledPin = 13;
const int inputPin = 12;
const int debounceDelay = 30;
boolean prev_state;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  myDFPlayer.begin(mySerial);

  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  prev_state = false;
  randomSeed(micros());

 // Serial.println(myDFPlayer.readFileCounts( )); //read all file counts in SD card


}

void loop() {
  if (debounce(inputPin)) {

    if (prev_state == false) {
      chooseAndPlay();
      prev_state = true;
    }

    digitalWrite(ledPin, HIGH);

  } else {
    prev_state = false;
    digitalWrite(ledPin, LOW);
  }
}


void chooseAndPlay() {
  randomSeed(micros());
  int song = int(random(1, number_of_songs + 1));
  myDFPlayer.play(song);
  randomSeed(micros());
  Serial.println(song);


}


boolean debounce(int pin) {
  boolean state;
  boolean prevState;

  prevState = digitalRead(pin);
  for (int i = 0 ; i < debounceDelay ; i ++) {
    delay(1);
    state = digitalRead(pin);
    if (state != prevState) {
      i = 0 ;
      prevState = state;
    }

  }
  return state;
}
