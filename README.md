# MIDIController
MIDI Controller using Arduino IDE, HairlessMIDI and loopMIDI

This project is an Arduino-based MIDI controller using an ATmega328 microcontroller. It sends MIDI messages via 8 buttons and 2 potentiometers for note-on, note-off, and control-change events.

#Hardware Requirements
Microcontroller: ATmega328 (e.g., Arduino Uno)
Buttons: 8 push buttons
Potentiometers: 2 analog pots
MIDI Interface: USB (via MIDI library)

#Features
8 Buttons: Send MIDI note-on/note-off messages.
2 Potentiometers: Send CC messages, mapped to 0-127.
Debouncing: Prevents multiple triggers from a single press.
MIDI Communication: Uses the MIDI Library.

#Setup
Install MIDI Library via Arduino IDE’s Library Manager.
Wire Buttons to pins 7, 8, 9, 5, 6, 2, 3, 4.
Wire Pots to A0, A1.
Upload the Code to the Arduino and use a MIDI tool or DAW to test.

#Configuration
note: Starting note number (default: 48).
cc: Starting Control Change number (default: 1).
varThreshold: Minimum pot movement to send CC.

#License
Open-source. Modify freely.
