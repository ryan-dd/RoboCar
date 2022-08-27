#include "Arduino.h"

struct Motor
{
  uint8_t ena = 0;
  uint8_t in1 = 0;
  uint8_t in2 = 0;
};

void motor_init(Motor m);
void motor_forward(Motor m);
void motor_reverse(Motor m);
void motor_set_speed(Motor m, uint8_t speedVal);
