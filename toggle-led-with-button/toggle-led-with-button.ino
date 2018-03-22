const int button_pin = 8;
const int led_pin = 13;

bool led_status = LOW;
bool button_status = LOW;
bool prev_button_status = LOW;

void setup() { 
  pinMode(led_pin, OUTPUT); 
  pinMode(button_pin, INPUT_PULLUP);                        // Set the internal pull up resistor, unpressed button is HIGH
}

void loop() {
  button_status = digitalRead(button_pin);                  // Get the current state of the button
  if (button_status == HIGH && prev_button_status == LOW) { // Has the button gone high since we last read it?
    led_status = !led_status;
    digitalWrite(led_pin, led_status);
  }
  prev_button_status = button_status;                       // Store the button's state
}

