#ifndef latch_h
#define latch_h
#include <Arduino.h>
#define CLOSE 11
#define OPEN 12

#define RATCHET 7
#define NEUTRAL 6
#define HALFLATCH 3
#define FULLLATCH 8
#define CLOSESWITCH 14


class Latch {
  public:
    Latch();
    void begin();
    bool close();
    bool open();
    bool neutral_state(bool fromClose);
};
#endif