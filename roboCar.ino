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

  Serial.begin(11520);
}

void loop()
{

}
