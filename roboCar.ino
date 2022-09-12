#include "Motor.h"
#include "Servo.h"
#include "Ultrasonic.h"
#include "DHT.h"

Motor motor1;
Motor motor2;
Servo s;
Ultrasonic ultra;
DHT dht(10, DHT22);

void setup()
{
  Serial.begin(9600);

  // Starboard
  motor1.ena = 5;
  motor1.in1 = 8;
  motor1.in2 = 7;
  motor_init(motor1);

  // Port
  motor2.ena = 6;
  motor2.in1 = 12;
  motor2.in2 = 13;
  motor_init(motor2);

  ultra.trigPin = 4;
  ultra.echoPin = 11;
  ultrasonic_init(ultra);

  uint8_t servoPin = 9;
  s.attach(servoPin);
//
  dht.begin();
  s.write(90); // range is 0 - 180
  delay(1000); // Gives me some time to reset the robot
}

const uint8_t forwardSpeed = 255; // 0 to 255
const uint8_t turningSpeed = 255; // 0 to 255
const int turnTime_ms = 583;

void robocar_go_forward(const Motor& motor1, const Motor& motor2)
{
  motor_forward(motor1);
  delay(1);
  motor_forward(motor2);
  delay(1);
  motor_set_speed(motor1, forwardSpeed);
  delay(1);
  motor_set_speed(motor2, forwardSpeed);
}

void robocar_turn_right(const Motor& motor1, const Motor& motor2)
{
  motor_forward(motor2);
    delay(1);

  motor_reverse(motor1);
    delay(1);

  motor_set_speed(motor1, turningSpeed);
    delay(1);

  motor_set_speed(motor2, turningSpeed);
    delay(1);

}

void robocar_turn_left(const Motor& motor1, const Motor& motor2)
{
  motor_reverse(motor2);
    delay(1);

  motor_forward(motor1);
    delay(1);

  motor_set_speed(motor1, turningSpeed);
    delay(1);

  motor_set_speed(motor2, turningSpeed);
    delay(1);

}

const unsigned long detectThreshold_cm = 72;
const int ultrasonicDelay_ms = 250;
void do_robo()
{
  s.write(90);
  delay(ultrasonicDelay_ms);
  
  robocar_go_forward(motor1, motor2);
  
  if(ultrasonic_get_dist_cm(ultra) < detectThreshold_cm)
  {
    // Something is close ahead, so stop
    motor_set_speed(motor1, 0);
    motor_set_speed(motor2, 0);

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
      robocar_turn_left(motor1, motor2);
      delay(turnTime_ms*2);
    }
    else if(leftDist > rightDist)
    {
      robocar_turn_left(motor1, motor2);
      delay(turnTime_ms);
    }
    else
    {
      robocar_turn_right(motor1, motor2);
      delay(turnTime_ms);
    }
  }

}

void loop()
{
  do_robo();
//  s.write(0);
//  do_robo();
//  robocar_go_forward(motor1, motor2);
//  motor_set_speed(motor2, 200);
//  motor_reverse(motor2);
//  delay(100);
//  motor_test(motor1, motor2);
//  robocar_turn_left(motor1, motor2);
//  do_robo();
  // TODO use humidity and temp for speed of sound measurements

//  Serial.println("Humidity: ");
//  delay(1000); 
//  float humidity = dht.readHumidity();
//  delay(1000); 
//  Serial.println(humidity);
//  delay(1000); 
//
//  Serial.println("Temperature: ");
//  float temperatureCelsius = dht.readTemperature();
//  delay(1000); 
//  Serial.println(temperatureCelsius);
//  delay(1000); // Gives me some time to reset the robot

//  float distance = ultrasonic_get_dist_cm(ultra);
//  if(distance < 40)
//  {
//  s.write(0); // range is 0 - 180
//  delay(10); // Gives me some time to reset the robot
////  Serial.println(distance);
//  }
//  else
//  {
//  s.write(90); // range is 0 - 180
//      delay(10); // Gives me some time to reset the robot
//  }

//  s.write(0); // range is 0 - 180
//  delay(1000); // Gives me some time to reset the robot
//  s.write(90); // range is 0 - 180
//  delay(1000); // Gives me some time to reset the robot
//  s.write(180); // range is 0 - 180
//  delay(1000); // Gives me some time to reset the robot

}
