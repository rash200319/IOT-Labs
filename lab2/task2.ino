#include <Keypad.h>

// --- Keypad Pins ---
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Wiring based on our new map
byte rowPins[ROWS] = {9, 10, 11, 12}; 
byte colPins[COLS] = {13, A0, A1, A2}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- 7-Segment Pins (2 to 8) ---
// Pin 2=a, 3=b, 4=c, 5=d, 6=e, 7=f, 8=g
const int segPins[] = {2, 3, 4, 5, 6, 7, 8};

// Common Anode Bitmask (0 = ON, 1 = OFF)
byte segmentMap[] = {
  0b11000000, // 0
  0b11111001, // 1
  0b10100100, // 2
  0b10110000, // 3
  0b10011001, // 4
  0b10010010, // 5
  0b10000010, // 6
  0b11111000, // 7
  0b10000000, // 8
  0b10010000, // 9
  0b10001000, // A
  0b10000011, // B
  0b11000110, // C
  0b10100001  // D
};

unsigned long lastSwitchTime = 0;
int currentIdx = 0;

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
    digitalWrite(segPins[i], HIGH); // Start with display OFF
  }
}

void loop() {
  keypad.getKeys(); // Update the status of all keys
  
  String active = "";
  // Check which keys are currently being held
  for (int i=0; i<LIST_MAX; i++) {
    if (keypad.key[i].kstate == PRESSED || keypad.key[i].kstate == HOLD) {
      active += keypad.key[i].kchar;
    }
  }

  if (active.length() > 0) {
    // If more than one key, swap every 500ms
    if (millis() - lastSwitchTime >= 500) {
      lastSwitchTime = millis();
      currentIdx = (currentIdx + 1) % active.length();
    }
    displayChar(active[currentIdx]);
  } else {
    clearDisplay();
  }
}

void displayChar(char c) {
  int val = -1;
  if (c >= '0' && c <= '9') val = c - '0';
  else if (c >= 'A' && c <= 'D') val = 10 + (c - 'A');
  
  if (val != -1) {
    for (int i = 0; i < 7; i++) {
      digitalWrite(segPins[i], bitRead(segmentMap[val], i));
    }
  } else {
    // Show a middle dash for '*' or '#'
    clearDisplay();
    digitalWrite(8, LOW); // Pin 8 is Segment G
  }
}

void clearDisplay() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], HIGH);
  }
}