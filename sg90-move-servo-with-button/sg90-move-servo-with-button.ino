#include <Servo.h>

Servo servo;
const int servo_pin = 8;
int servo_angle = 0;

const int button_pin = 10;

void setup() {
  servo.attach(servo_pin);
  servo.write(servo_angle);
  pinMode(button_pin, INPUT_PULLUP); // Set the internal pull up resistor, unpressed button is HIGH
}

void loop() {
  if (digitalRead(button_pin) == LOW) { // if button is pressed
    if (servo_angle == 0) {
      servo_angle = 90;
    } else {
      servo_angle = 0;
    }
    servo.write(servo_angle);
    delay(500);
  }
}
