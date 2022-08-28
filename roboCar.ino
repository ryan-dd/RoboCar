#include "Motor.h"
#include "Servo.h"
#include "Ultrasonic.h"
#include "DHT.h"

Motor m1;
Motor m2;
Servo s;
Ultrasonic ultra;
uint8_t servoPin = 9;

void setup()
{
  m1.ena = 3;
  m1.in1 = 4;
  m1.in2 = 5;
  motor_init(m1);

  m2.ena = 6;
  m2.in1 = 7;
  m2.in2 = 8;
  motor_init(m2);

  ultra.pin = 10;
  ultrasonic_init(ultra);

  s.attach(servoPin);

  // TODO use humidity and temp for speed of sound measurements
  DHT dht(2, DHT22);
  float humidity = dht.readHumidity();
  float temperatureCelsius = dht.readTemperature();

  s.write(90); // range is 0 - 180
  Serial.begin(11520);
}

const uint8_t forwardSpeed = 250; // 0 to 255
const uint8_t turningSpeed = 200; // 0 to 255
const int turnTime_ms = 200;

void robocar_go_forward(const Motor& m1, const Motor& m2)
{
  motor_forward(m1);
  motor_forward(m2);
  motor_set_speed(m1, forwardSpeed);
  motor_set_speed(m2, forwardSpeed);
}

void robocar_turn_right(const Motor& m1, const Motor& m2)
{
  motor_forward(m1);
  motor_reverse(m2);
  motor_set_speed(m1, turningSpeed);
  motor_set_speed(m2, turningSpeed);
}

void robocar_turn_left(const Motor& m1, const Motor& m2)
{
  motor_reverse(m1);
  motor_forward(m2);
  motor_set_speed(m1, turningSpeed);
  motor_set_speed(m2, turningSpeed);
}

const unsigned long detectThreshold_cm = 20;
const int ultrasonicDelay_ms = 250;
void loop()
{
  if(ultrasonic_get_dist_cm(ultra) < detectThreshold_cm)
  {
    // Something is close ahead, so stop
    motor_set_speed(m1, 0);
    motor_set_speed(m2, 0);

    // Look to see which direction to go (ultrasonic sensor is mounted on servo)
    s.write(0); // servo moves to 0 degrees
    // Give some time for the servo to move in the right place before taking a reading
    delay(ultrasonicDelay_ms);
    unsigned long rightDist = ultrasonic_get_dist_cm(ultra);
    delay(ultrasonicDelay_ms);

    s.write(180);
    delay(ultrasonicDelay_ms);
    unsigned long leftDist = ultrasonic_get_dist_cm(ultra);
    delay(ultrasonicDelay_ms);

    if(leftDist < detectThreshold_cm && rightDist < detectThreshold_cm)
    {
      // We are in a corner, turn around 180!
      robocar_turn_left(m1, m2);
      delay(turnTime_ms*2);
    }
    else if(leftDist > rightDist)
    {
      robocar_turn_left(m1, m2);
      delay(turnTime_ms);
    }
    else
    {
      robocar_turn_right(m1, m2);
      delay(turnTime_ms);
    }
  }

  robocar_go_forward(m1, m2);
}
