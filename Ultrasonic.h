#include "Arduino.h"

struct Ultrasonic
{
  uint8_t trigPin;
  uint8_t echoPin;
};

void ultrasonic_init(Ultrasonic ultra);
long ultrasonic_get_dist_cm(Ultrasonic ultra);
