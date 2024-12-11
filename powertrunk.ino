#include "Latch.h"
#include "Trunk.h"

#define BCM 2
#define INTERNAL_BUTTON A1

Latch latch;
Trunk trunk;

void setup() {
  Serial.begin(115200);
  latch.begin();
  trunk.begin();
}

void loop() {
  int half_latch = digitalRead(HALFLATCH);
  int full_latch = digitalRead(FULLLATCH);
  int close = digitalRead(CLOSESWITCH);
  if (half_latch && !full_latch && close) {
    latch.close();
  }
  checkSerialInput(); 
}

void checkSerialInput() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == 'S') {
      Serial.print("Neutral pin, state: ");
      Serial.print(digitalRead(NEUTRAL));
      Serial.println();
      Serial.print("Half latch pin, state: ");
      Serial.print(digitalRead(HALFLATCH));
      Serial.println();
      Serial.print("Full latch pin, state: ");
      Serial.print(digitalRead(FULLLATCH));
      Serial.println();
      Serial.print("Ratchet pin state: ");
      Serial.print(digitalRead(RATCHET));
      Serial.println();
      Serial.print("Close swicth pin state: ");
      Serial.print(digitalRead(CLOSESWITCH));
      Serial.println();
    }
    if (input == 'N') {
      latch.neutral_state(true);
    }
    if (input == 'P') {
      latch.neutral_state(false);
    }
    if (input == 'O') {
      latch.open();
    }
    if (input == 'C') {
      latch.close();
    }
  }
}