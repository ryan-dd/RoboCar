#include "Motor.h"

void motor_init(Motor m)
{
  pinMode(m.in1, OUTPUT);
  pinMode(m.in2, OUTPUT);
  pinMode(m.ena, OUTPUT);
}

void motor_forward(Motor m)
{
  digitalWrite(m.in1, HIGH);
  digitalWrite(m.in2, LOW);  
}

void motor_reverse(Motor m)
{
  digitalWrite(m.in1, LOW);
  digitalWrite(m.in2, HIGH);  
}

void motor_set_speed(Motor m, uint8_t speedVal)
{
  analogWrite(m.ena, speedVal);
}

void motor_test(Motor m1, Motor m2)
{
  motor_forward(m1);
  motor_reverse(m2);
  motor_set_speed(m1, 200);
  motor_set_speed(m2, 200);
  delay(1000);

  motor_set_speed(m1, 0);
  motor_set_speed(m2, 0);
  delay(1000);

  motor_reverse(m1);
  motor_forward(m2);
  motor_set_speed(m1, 200);
  motor_set_speed(m2, 200);
  delay(1000);

  motor_set_speed(m1, 0);
  motor_set_speed(m2, 0);
  delay(1000);
}
