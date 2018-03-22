const int red_pin = 7;
const int yellow_pin = 8;
const int green_pin = 9;

void setup() {
  pinMode(red_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
}

void loop() {
  setLeds(LOW, LOW, HIGH);
  delay(2000);

  setLeds(LOW, HIGH, LOW);
  delay(1000);

  setLeds(HIGH, LOW, LOW);
  delay(4000);
}

void setLeds(bool red, bool yellow, bool green) {
  digitalWrite(red_pin, red);
  digitalWrite(yellow_pin, yellow);
  digitalWrite(green_pin, green);
}
