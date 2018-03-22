#define AND
//#define OR
//#define XOR

const int button_pin_1 = 8;
const int button_pin_2 = 9;
const int led_pin = 13;

bool button_status_1 = LOW;
bool button_status_2 = LOW;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin_1, INPUT_PULLUP);        // Set the internal pull up resistor, unpressed button is HIGH
  pinMode(button_pin_2, INPUT_PULLUP);
}

void loop() {
  button_status_1 = digitalRead(button_pin_1);  // Get the current state of the first button
  button_status_2 = digitalRead(button_pin_2);  // Get the current state of the second button

  // Light the led accordingly to which logical gate is defined
#if defined(AND)
  digitalWrite(led_pin, !button_status_1 && !button_status_2);
#elif defined(OR)
  digitalWrite(led_pin, !button_status_1 || !button_status_2);
#elif defined(XOR)
  digitalWrite(led_pin, !button_status_1 ^ !button_status_2);
#endif

}

