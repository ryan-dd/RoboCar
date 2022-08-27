#include "Arduino.h"

struct Ultrasonic
{
  uint8_t pin;
};

void ultrasonic_init(Ultrasonic ultra);
unsigned long ultrasonic_get_dist_cm(Ultrasonic ultra);

