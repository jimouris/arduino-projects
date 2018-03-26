#define LEDS 4

const int pot_pin = A0;
const int led_pins[LEDS] = { 2, 4, 6, 8 };

int pot_val = 0;
int led_num = 0;

void setup() {
  for (int i = 0 ; i < LEDS ; i++) {
    pinMode(led_pins[i], OUTPUT);
  }
}

void loop() {
  pot_val = analogRead(pot_pin);            // read the analog value of potentiometer
  led_num = map(pot_val, 0, 1024, 0, LEDS); // map it to the number of the leds
  setLed(led_num);                          // set led_num to HIGH, and all the others to LOW
}

void setLed(int led_num) {
  digitalWrite(led_pins[led_num], HIGH);
  for (int i = 0 ; i < LEDS ; i++) {
    if (i != led_num) {
      digitalWrite(led_pins[i], LOW);
    }
  }
}
