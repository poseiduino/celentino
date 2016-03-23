/*
  Celentino

 Plays melodies

 circuit:
 * 8-ohm speaker on digital pin 8

 created 23 Mar 2016
 by Poseiduino

 See also:
 
 http://www.arduino.cc/en/Tutorial/Tone

 */

#include "pitches.h"

const int buttonPin = 2;
const int nextPin = 4;
const int repeatPin = 7;
const int ledPin =  13;
int buttonState = 1;
int nextState = 1; 
int repeatState = 1; 
bool blocked = false;

const unsigned char LAUTSPRECHER_PIN = 8;
unsigned int GANZE_NOTE = 1000;

struct Note {
  Tonhoehe frequenz;
  int laenge;
};

Note tuetataa[] = {
  {NOTE_F4, 4}, {NOTE_C4, 4}, {NOTE_F4, 2}, {PAUSE, 2}, 
  {NOTE_C4, 4}, {NOTE_F4, 4}, {NOTE_C4, 4}, {NOTE_F4, 2}, {PAUSE, 2} 
};

// Alle meine Entchen
Note entchen[] = {
  {NOTE_C4, 4}, {NOTE_D4, 4}, {NOTE_E4, 4}, {NOTE_F4, 4}, {NOTE_G4, 2}, {NOTE_G4, 2},
  {NOTE_A4, 4}, {NOTE_A4, 4}, {NOTE_A4, 4}, {NOTE_A4, 4}, {NOTE_G4, 1}, {PAUSE, 4},
  {NOTE_A4, 4}, {NOTE_A4, 4}, {NOTE_A4, 4}, {NOTE_A4, 4}, {NOTE_G4, 1}, {PAUSE, 4},
  {NOTE_F4, 4}, {NOTE_F4, 4}, {NOTE_F4, 4}, {NOTE_F4, 4}, {NOTE_E4, 2}, {NOTE_E4, 2},
  {NOTE_D4, 4}, {NOTE_D4, 4}, {NOTE_D4, 4}, {NOTE_D4, 4}, {NOTE_C4, 1}
};

// Der Kuckkuck und der Esel
Note kuckuck[] = {
  {NOTE_G4, 4}, {NOTE_E4, 4}, {NOTE_G4, 4}, {NOTE_E4, 4}, {NOTE_G4, 4},
  {NOTE_F4, 4}, {NOTE_F4, 2},
  {NOTE_F4, 4}, {NOTE_D4, 4}, {NOTE_F4, 4}, {NOTE_D4, 4}, {NOTE_F4, 4}, {NOTE_E4, 2},
  {NOTE_G4, 8}, {NOTE_F4, 8}, {NOTE_E4, 4}, {NOTE_E4, 4}, {NOTE_E4, 4}, {NOTE_E4, 4}, {NOTE_F4, 4}, {NOTE_F4, 2},
  {NOTE_F4, 8}, {NOTE_E4, 8}, {NOTE_D4, 4}, {NOTE_D4, 4}, {NOTE_D4, 4}, {NOTE_D4, 4}, {NOTE_E4, 4}, {NOTE_E4, 2},
  {NOTE_C4, 4}, {NOTE_C4, 4}, {NOTE_D4, 4}, {NOTE_E4, 4}, {NOTE_F4, 4}, {NOTE_G4, 2}, {NOTE_A4, 8}, {NOTE_G4, 4},
  {NOTE_F4, 4}, {NOTE_E4, 4}, {NOTE_E4, 4}, {NOTE_D4, 4}, {NOTE_D4, 4}, {NOTE_C4, 1}
};

Note leevsten[] = {
  {NOTE_F4, 4}, {NOTE_A4, 4}, {NOTE_C4, 4},
  {NOTE_G4, 4}, {NOTE_G4, 8}, {NOTE_E4, 8}, {NOTE_C5, 4},
  {NOTE_F4, 4}, {NOTE_A4, 4}, {NOTE_C5, 4},
  {NOTE_G4, 2}, {PAUSE, 4},
  {NOTE_AS4, 4}, {NOTE_D5, 8}, {NOTE_C5, 8}, {NOTE_AS4, 4},
  {NOTE_A4, 4}, {NOTE_C5, 8}, {NOTE_AS4, 8}, {NOTE_A4, 4},
  {NOTE_G4, 4}, {NOTE_F4, 4}, {NOTE_G4, 4},
  {NOTE_A4, 4}, {NOTE_C5, 4},
  {NOTE_AS4, 4}, {NOTE_D5, 8}, {NOTE_C5, 8}, {NOTE_AS4, 4},
  {NOTE_A4, 4}, {NOTE_C5, 8}, {NOTE_AS4, 8}, {NOTE_A4, 4},
  {NOTE_G4, 4}, {NOTE_F4, 4}, {NOTE_E4, 4},
  {NOTE_F4, 1}
};

//Note starwars[] = {
//  {NOTE_C4, 8}, {NOTE_C4, 4}, 
//  {NOTE_F4, 2}, {NOTE_C5, 2},
//  {NOTE_AS4, 8}, {NOTE_A4, 8}, {NOTE_G4, 4}, {NOTE_F5, 1}, {NOTE_C5, 1},
//  {NOTE_AS4, 8}, {NOTE_A4, 8}, {NOTE_G4, 4}, {NOTE_F5, 1}, {NOTE_C5, 1},
//  {NOTE_AS4, 8}, {NOTE_A4, 8}, {NOTE_AS4, 4}, {NOTE_G4, 1}
//};

Note harung[] = {
  {NOTE_D4, 8}, {NOTE_E4, 8}, {NOTE_FS4, 8},
  {NOTE_G4, 4}, {NOTE_G4, 4}, {NOTE_FS4, 4}, {NOTE_E4, 4},
  {NOTE_FS4, 4}, {NOTE_D4, 4}, {NOTE_E4, 4}, {NOTE_D4, 4},
  {NOTE_FS4, 4}, {NOTE_FS4, 4}, {NOTE_FS4, 3}, {NOTE_D4, 8},
  {NOTE_G4, 4}, {NOTE_G4, 4}, {NOTE_G4, 8},
  {NOTE_D4, 8}, {NOTE_E4, 8}, {NOTE_FS4, 8},
  {NOTE_G4, 4}, {NOTE_G4, 4}, {NOTE_FS4, 4}, {NOTE_E4, 4},
  {NOTE_FS4, 4}, {NOTE_D4, 4}, {NOTE_E4, 4}, {NOTE_D4, 4},
  {NOTE_FS4, 4}, {NOTE_FS4, 4}, {NOTE_FS4, 3}, {NOTE_D4, 8},
  {NOTE_G4, 4}, {NOTE_G4, 4}, {NOTE_G4, 8},
  {NOTE_G4, 4}, 
  {NOTE_A4, 3}, {NOTE_G4, 8}, {NOTE_FS4, 4}, {NOTE_E4, 4}, 
  {NOTE_E4, 4}, {NOTE_D4, 4}, {PAUSE, 8}, {NOTE_B4, 8}, {NOTE_B4, 8}, {NOTE_B4, 8},
  {NOTE_B4, 4}, {NOTE_A4, 4}, {PAUSE, 8}, {NOTE_C5, 8}, {NOTE_C5, 8}, {NOTE_C5, 8},
  {NOTE_C5, 4}, {NOTE_B4, 4}, {PAUSE, 4},
  {NOTE_G4, 4}, 
  {NOTE_A4, 3}, {NOTE_G4, 8}, {NOTE_FS4, 4}, {NOTE_E4, 4}, 
  {NOTE_E4, 4}, {NOTE_D4, 4}, {PAUSE, 8}, {NOTE_B4, 8}, {NOTE_B4, 8}, {NOTE_B4, 8},
  {NOTE_B4, 4}, {NOTE_A4, 4}, {NOTE_C5, 4}, {NOTE_FS4, 4}, {NOTE_G4, 3}
};

Note buntwaelder[] = {
  {NOTE_G4, 4}, {NOTE_G4, 8}, {NOTE_G4, 8}, {NOTE_FS4, 8}, {NOTE_G4, 8},
  {NOTE_A4, 3}, {NOTE_G4, 3},
  {NOTE_B4, 4}, {NOTE_B4, 8}, {NOTE_B4, 8}, {NOTE_A4, 8}, {NOTE_B4, 8},
  {NOTE_C5, 3}, {NOTE_B4, 3},
  {NOTE_A4, 4}, {NOTE_A4, 8}, {NOTE_G4, 8}, {NOTE_B4, 8}, {NOTE_CS4, 8},
  {NOTE_D4, 3}, {PAUSE, 3},
  {NOTE_B4, 4}, {NOTE_A4, 8}, {NOTE_G4, 4}, {NOTE_FS4, 8}, 
  {NOTE_E4, 3}, {NOTE_E4, 3},
  {NOTE_C5, 4}, {NOTE_B4, 8}, {NOTE_A4, 8}, {NOTE_B4, 8}, {NOTE_G4, 8},
  {NOTE_FS4, 3}, {NOTE_FS4, 3},
  {NOTE_G4, 8}, {NOTE_B4, 8}, {NOTE_D5, 8}, {NOTE_D4, 8}, {NOTE_E4, 8}, {NOTE_FS4, 8},
  {NOTE_G4, 2}
};

int r = 0;
unsigned int anzahlnoten = 0;

void setup() {
  //Setup hardware
  pinMode(buttonPin, INPUT);
  pinMode(nextPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  anzahlnoten = sizeof(tuetataa)/sizeof(tuetataa[0]);
  playMelodie(tuetataa);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW & !blocked) {
    blocked = true;
    digitalWrite(ledPin, HIGH);
    r = differentRandom();
    chooseMelodie();
  } else {
    digitalWrite(ledPin, LOW);
  }

  nextState = digitalRead(nextPin);
  if (nextState == LOW & !blocked) {
    blocked = true;
    r++;
    if (r == 5) {
      r = 0;
    }
    chooseMelodie(); 
  }

  repeatState = digitalRead(repeatPin);
  if (repeatState == LOW & !blocked) {
    Serial.println("Repeat - Button 7");
    blocked = true;
    chooseMelodie();
  }
}

void chooseMelodie() {
   switch(r) {
      case 0:
        anzahlnoten = sizeof(entchen)/ sizeof(entchen[0]);
        playMelodie(entchen);
        break;
      case 1:
        anzahlnoten = sizeof(kuckuck)/ sizeof(kuckuck[0]);
        playMelodie(kuckuck);
        break;
      case 2:
        anzahlnoten = sizeof(leevsten)/ sizeof(leevsten[0]);
        playMelodie(leevsten);
        break;
      case 3:
        anzahlnoten = sizeof(harung)/ sizeof(harung[0]);
        playMelodie(harung);
        break;
      case 4:
        GANZE_NOTE = 1800;
        anzahlnoten = sizeof(buntwaelder)/ sizeof(buntwaelder[0]);
        playMelodie(buntwaelder);
        GANZE_NOTE = 1000;
        break;
    }
}

void playMelodie(Note *melodie) {
  blocked = false;
  for (unsigned int thisNote = 0; thisNote < anzahlnoten; thisNote++) {
    unsigned int noteDuration = GANZE_NOTE / melodie[thisNote].laenge;
    unsigned int pauseBetweenNotes = noteDuration * 1.30;
    tone(LAUTSPRECHER_PIN, melodie[thisNote].frequenz, noteDuration);
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(LAUTSPRECHER_PIN);
  }
}

unsigned int differentRandom() {
  int i = random(0,4);
  while (r == i) {
    i = random(0,4);
  }
  return i;
} 
