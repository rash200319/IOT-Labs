/*
 * 8-Key Summing Tone Generator (Fixed 20ms Tap + Hold)
 * Buttons: Pins 2-9 (INPUT_PULLUP)
 * Speaker: Pin 10
 */

const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int frequencies[] = {300, 400, 500, 600, 700, 800, 900, 1000};
const int speakerPin = 10;

bool lastState[8];               // previous button state
unsigned long tapEndTime[8];     // until when to keep playing the tone

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastState[i] = HIGH;       // buttons start unpressed
    tapEndTime[i] = 0;
  }

  pinMode(speakerPin, OUTPUT);
}

void loop() {
  unsigned long totalFrequency = 0;
  unsigned long currentTime = millis();

  for (int i = 0; i < 8; i++) {
    bool currentState = digitalRead(buttonPins[i]);

    //Detect edge: new press
    if (currentState == LOW && lastState[i] == HIGH) {
      tapEndTime[i] = currentTime + 20; // play for at least 20ms
    }

    // Check if the button is being held or within 20ms tap window
    if (currentState == LOW || currentTime < tapEndTime[i]) {
      totalFrequency += frequencies[i];
    }

    lastState[i] = currentState;
  }

  // Play summed frequency if any
  if (totalFrequency > 0) {
    tone(speakerPin, totalFrequency);
  } else {
    noTone(speakerPin);
  }

  delay(5); // debounce
}