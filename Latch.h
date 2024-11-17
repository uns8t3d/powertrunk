#ifndef latch_h
#define latch_h
#include <Arduino.h>
#define CLOSE 5
#define OPEN 6

#define RATCHET 10
#define NEUTRAL 7
#define HALFLATCH 8
#define FULLLATCH 9
#define CLOSESWITCH 11


class Latch {
  public:
    Latch();
    void begin();
    bool close();
    bool open();
    bool neutral_state(bool fromClose);
};
#endif