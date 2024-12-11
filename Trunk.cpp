#include "Trunk.h"
#include <EnableInterrupt.h>

int hall_a;
int hall_b;
bool is_open;

volatile int position = 0;
volatile byte lastState = 0;

Trunk::Trunk() {

}

void Trunk::begin() {
  pinMode(BEEPER, OUTPUT);
  pinMode(TRUNK_CLUTCH, OUTPUT);
  pinMode(TRUNK_OPEN, OUTPUT);
  pinMode(TRUNK_CLOSE, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(HALLA, INPUT_PULLUP);
  pinMode(HALLB, INPUT_PULLUP);
  digitalWrite(BEEPER, LOW);
  digitalWrite(TRUNK_CLUTCH, LOW);
  digitalWrite(TRUNK_OPEN, LOW);
  digitalWrite(TRUNK_CLOSE, LOW);
  analogWrite(MOTOR_PWM, PWM_SPEED);

  pinMode(HALLA, INPUT_PULLUP);
  pinMode(HALLB, INPUT_PULLUP);
  pinMode(CURRENT_SENSOR, INPUT_PULLUP);
  enableInterrupt(HALLA, update_hall, CHANGE);
  enableInterrupt(HALLB, update_hall, CHANGE);
}

void Trunk::open() {
  digitalWrite(TRUNK_CLOSE, LOW);
  digitalWrite(TRUNK_OPEN, HIGH);
}

void Trunk::close() {
  digitalWrite(TRUNK_OPEN, LOW);
  digitalWrite(TRUNK_CLOSE, HIGH);
}

void Trunk::stop() {
  digitalWrite(TRUNK_OPEN, LOW);
  digitalWrite(TRUNK_CLOSE, LOW);
}

void Trunk::clutch(bool state) {
  if (state) {
    digitalWrite(TRUNK_CLUTCH, HIGH);
  } else {
    digitalWrite(TRUNK_CLUTCH, LOW);
  }
}

bool Trunk::measure_current() {
  return CURRENT_LIMIT > analogRead(CURRENT_SENSOR);
}

void Trunk::hall_measure() {

}

void Trunk::update_hall() {
  byte currentState = (digitalRead(HALLA) << 1) | digitalRead(HALLB);

  if ((lastState == 0b00 && currentState == 0b01) ||
      (lastState == 0b01 && currentState == 0b11) ||
      (lastState == 0b11 && currentState == 0b10) ||
      (lastState == 0b10 && currentState == 0b00)) {
    position++;
  } else if ((lastState == 0b00 && currentState == 0b10) ||
             (lastState == 0b10 && currentState == 0b11) ||
             (lastState == 0b11 && currentState == 0b01) ||
             (lastState == 0b01 && currentState == 0b00)) {
    position--;
  }
  lastState = currentState;
}

int Trunk::get_position() {
  return lastState;
}