/**
 *             MFRC522      Arduino Uno
 * Signal      Pin          Pin
 * RST/Reset   RST          9
 * SPI SS      SDA(SS)      10
 * SPI MOSI    MOSI         11 / ICSP-4
 * SPI MISO    MISO         12 / ICSP-1
 * SPI SCK     SCK          13 / ICSP-3
**/

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// RFID
const int RST_PIN = 9;
const int SS_PIN = 10;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

const int auth_cards_num = 2;
String auth_cards[auth_cards_num] = {"D0 5C 1D A4", "00 00 00 00"};

// Leds
const int led_success_pin = 2;
const int led_failure_pin = 4;

// Servo
Servo servo;
const int servo_pin = 6;
int servo_angle = 0;


void setup() {
  // Leds
  pinMode(led_success_pin, OUTPUT);
  pinMode(led_failure_pin, OUTPUT);
  // Servo
  servo.attach(servo_pin);
  servo.write(servo_angle);
  // RFID
  Serial.begin(9600);   // Initiate a serial communication
  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  Serial.println(F("Ready to use.\n"));
}

void loop() {
  // Look for new cards, and select one if present
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return ;
  }
  // Show UID on serial monitor
  String card_uid = read_and_print_UID();

  bool authorized = false;
  for (int i = 0 ; i < auth_cards_num ; i++) {
    if (card_uid == auth_cards[i]) {
      authorized = true;
      break;
    }
  }
  if (authorized) {
    Serial.println(F("\nAuthorized access\n"));
    digitalWrite(led_success_pin, HIGH);
    if (servo_angle == 0) {
      servo_angle = 90;
    } else {
      servo_angle = 0;
    }
    servo.write(servo_angle);
  } else {
    Serial.println(F("\nAccess denied\n"));
    digitalWrite(led_failure_pin, HIGH);
  }
  delay(2000);
  digitalWrite(led_success_pin, LOW);
  digitalWrite(led_failure_pin, LOW);
}

String read_and_print_UID() {
  Serial.print(F("UID tag:"));
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  return content.substring(1);
}

