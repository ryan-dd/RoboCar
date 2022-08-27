#include "Ultrasonic.h"

void ultrasonic_init(Ultrasonic ultra)
{
  // No op for now
}

unsigned long ultrasonic_get_dist_cm(Ultrasonic ultra)
{
  // Send trigger for 10 us
  pinMode(ultra.pin, OUTPUT); 
  digitalWrite(ultra.pin, LOW);
  delayMicroseconds(2);

  digitalWrite(ultra.pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultra.pin, LOW);

  // Get the sound wave travel time in microseconds
  pinMode(ultra.pin, INPUT); 
  unsigned long pulseDuration_us = pulseIn(ultra.pin, HIGH);

  // cm_travelled = pulseDuration us * 1/1000000 s/us * 343 m/s * 100/1 cm/m;
  // cm_to_target = cm travelled / 2;
  return 0.01715 * pulseDuration_us;
}
