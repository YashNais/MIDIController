#define ATMEGA328 1

#ifdef ATMEGA328
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

#endif

const int N_BUTTONS = 8;
const int BUTTON_ARDUINO_PIN[N_BUTTONS] = {7,8,9,5,6,2,3,4};
int buttonCState[N_BUTTONS] = {};       
int buttonPState[N_BUTTONS] = {};

unsigned long lastDebounceTime[N_BUTTONS] = {0}; 
unsigned long debounceDelay = 50; 

const int N_POTS = 2; 
const int POT_ARDUINO_PIN[N_POTS] = {A0, A1};

int potCState[N_POTS] = {0}; 
int potPState[N_POTS] = {0}; 
int potVar = 0; 

int midiCState[N_POTS] = {0}; 
int midiPState[N_POTS] = {0}; 

const int TIMEOUT = 300; 
const int varThreshold = 10; 
boolean potMoving = true;
unsigned long PTime[N_POTS] = {0}; 
unsigned long timer[N_POTS] = {0};

byte midiCh = 1; 
byte note = 48; 
byte cc = 1; 

void setup() {

  Serial.begin(115200); //*

#ifdef DEBUG
Serial.println("Debug mode");
Serial.println();
#endif

  for (int i = 0; i < N_BUTTONS; i++) {
    pinMode(BUTTON_ARDUINO_PIN[i], INPUT_PULLUP);
  }

}
void loop() {

  buttons();
  potentiometers();

}

void buttons() {

  for (int i = 0; i < N_BUTTONS; i++) {

    buttonCState[i] = digitalRead(BUTTON_ARDUINO_PIN[i]);  

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {

      if (buttonPState[i] != buttonCState[i]) {
        lastDebounceTime[i] = millis();

        if (buttonCState[i] == LOW) {
#ifdef ATMEGA328

MIDI.sendNoteOn(note + i, 127, midiCh);

#elif DEBUG
Serial.print(i);
Serial.println(": button on");
#endif

        }
        else {

#ifdef ATMEGA328
MIDI.sendNoteOn(note + i, 0, midiCh); 

#elif DEBUG
Serial.print(i);
Serial.println(": button off");
#endif

        }
        buttonPState[i] = buttonCState[i];
      }
    }
  }
}

void potentiometers() {


  for (int i = 0; i < N_POTS; i++) { 

    potCState[i] = analogRead(POT_ARDUINO_PIN[i]); 

    midiCState[i] = map(potCState[i], 0, 1023, 0, 127); 

    potVar = abs(potCState[i] - potPState[i]); 
    if (potVar > varThreshold) { 
      PTime[i] = millis(); 
    }

    timer[i] = millis() - PTime[i]; 

    if (timer[i] < TIMEOUT) { 
      potMoving = true;
    }
    else {
      potMoving = false;
    }

    if (potMoving == true) { 
      if (midiPState[i] != midiCState[i]) {

#ifdef ATMEGA328
MIDI.sendControlChange(cc + i, midiCState[i], midiCh); 

#elif DEBUG
Serial.print("Pot: ");
Serial.print(i);
Serial.print(" ");
Serial.println(midiCState[i]);

#endif

        potPState[i] = potCState[i]; 
        midiPState[i] = midiCState[i];
      }
    }
  }
}