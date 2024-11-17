#include "Latch.h"


Latch::Latch() {

}

void Latch::begin() {
  pinMode(OPEN, OUTPUT);
  pinMode(CLOSE, OUTPUT);
  pinMode(RATCHET, INPUT_PULLUP);
  pinMode(NEUTRAL, INPUT_PULLUP);
  pinMode(HALFLATCH, INPUT_PULLUP);
  pinMode(FULLLATCH, INPUT_PULLUP);
  pinMode(CLOSESWITCH, INPUT_PULLUP);
}

bool Latch::open() {
  int full = digitalRead(FULLLATCH);
  int ratchet = digitalRead(RATCHET);
  int neutral = digitalRead(NEUTRAL);
  if (full || ratchet) {
    digitalWrite(OPEN, LOW);
    digitalWrite(CLOSE, HIGH);
    open();
  } else {
    digitalWrite(CLOSE, LOW);
    digitalWrite(OPEN, LOW);
    neutral_state(false);
    return true;
  }
}

bool Latch::close() {
  int full = digitalRead(FULLLATCH);
  int ratchet = digitalRead(RATCHET);
  if (!full || !ratchet) {
    digitalWrite(CLOSE, LOW);
    digitalWrite(OPEN, HIGH);
    close();
  } else {
    digitalWrite(CLOSE, LOW);
    digitalWrite(OPEN, LOW);
    neutral_state(true);
    return true;
  }
}

bool Latch::neutral_state(bool fromClose) {
  int neutral = digitalRead(NEUTRAL);
  if (fromClose && !neutral) {
    digitalWrite(OPEN, LOW);
    digitalWrite(CLOSE, HIGH);
    neutral_state(fromClose);
  } else if (!fromClose && neutral) {
    digitalWrite(CLOSE, LOW);
    digitalWrite(OPEN, HIGH);
    neutral_state(fromClose);
  } else {
    digitalWrite(OPEN, LOW);
    digitalWrite(CLOSE, LOW);
    return true;
  }
}