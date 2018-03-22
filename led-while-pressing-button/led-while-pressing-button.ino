const int button_pin = 8;
const int led_pin = 13;

bool button_status = LOW;

void setup() { 
  pinMode(led_pin, OUTPUT); 
  pinMode(button_pin, INPUT_PULLUP);        // Set the internal pull up resistor, unpressed button is HIGH
}

void loop() {
  button_status = digitalRead(button_pin);  // Get the current state of the button
  digitalWrite(led_pin, !button_status);    // If button_status == HIGH then led_status = LOW else led_status = HIGH
}

