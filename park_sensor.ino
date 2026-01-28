#define BUTTON A0

#define BUZZER 2
#define SENSOR_TRIG 3
#define SENSOR_ECHO 4

#define RED 5
#define GREEN 6
#define BLUE 7

#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); // RS=13, E=12, D4=11, D5=10, D6=9, D7=8

bool systemOn = false; // start OFF by default
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // ms

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(SENSOR_TRIG, OUTPUT);
  pinMode(SENSOR_ECHO, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("Park sensor");
  delay(1000);
  lcd.clear();
}

void loop() {
  // ---- BUTTON TOGGLE (FAST TAP, NO HOLD) ----
  bool reading = digitalRead(BUTTON);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    static bool lastStableState = HIGH;
    if (reading == LOW && lastStableState == HIGH) {
      systemOn = !systemOn; // toggle on quick press
    }
    lastStableState = reading;
  }

  lastButtonState = reading;

  // ---- IF SYSTEM OFF ----
  if (!systemOn) {
    noTone(BUZZER);
    analogWrite(RED, 255);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 255);
    return;
  }

  // ---- SENSOR READ ----
  digitalWrite(SENSOR_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(SENSOR_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENSOR_TRIG, LOW);

  unsigned long duration = pulseIn(SENSOR_ECHO, HIGH, 30000);
  unsigned long distance = duration / 58; // cm

  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  if (distance == 0) lcd.print("N/A   ");
  else {
    lcd.print(distance);
    lcd.print(" cm  ");
  }

  // ---- LED + BUZZER LOGIC ----
  int blinkDelay;
  int toneFreq;

  if (distance > 0 && distance < 11) {
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 255);
    blinkDelay = 100;
    toneFreq = 1500;
  } 
  else if (distance >= 5 && distance <= 30) {
    int greenVal = map(distance, 5, 30, 255, 0);
    analogWrite(RED, 0);
    analogWrite(GREEN, greenVal);
    analogWrite(BLUE, 255);
    blinkDelay = 300;
    toneFreq = 1000;
  } 
  else {
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 255);
    blinkDelay = 600;
    toneFreq = 600;
  }

  tone(BUZZER, toneFreq);
  delay(blinkDelay);
  noTone(BUZZER);
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
  delay(blinkDelay);
}
