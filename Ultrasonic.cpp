#include "Ultrasonic.h"

void ultrasonic_init(Ultrasonic ultra)
{
  pinMode(ultra.trigPin, OUTPUT);
  pinMode(ultra.echoPin, INPUT);
}

long ultrasonic_get_dist_cm(Ultrasonic ultra)
{
  uint8_t trigPin = ultra.trigPin;
  uint8_t echoPin = ultra.echoPin;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Set trigPin to HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // cm_travelled = pulseDuration us * 1/1000000 s/us * 343 m/s * 100/1 cm/m;
  // cm_to_target = cm travelled / 2;
  return duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}
