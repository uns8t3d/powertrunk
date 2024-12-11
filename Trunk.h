#ifndef trunk_h
#define trunk_h
#include <Arduino.h>

#define TRUNK_OPEN 9
#define TRUNK_CLOSE 10

#define TRUNK_CLUTCH 4
#define MOTOR_PWM 5

#define HALLA A4
#define HALLB A5
#define CURRENT_SENSOR A6

#define BEEPER A2

#define PWM_SPEED 180
#define CURRENT_LIMIT 400

extern volatile int position;
extern volatile byte lastState;

extern int hall_a;
extern int hall_b;
extern bool is_open;

class Trunk {
  public:
    Trunk();
    void begin();

    void open();
    void close();

    void clutch(bool state);
    void hall_measure();
    bool measure_current();

    void stop();
    static void update_hall();
    int get_position();
};
#endif