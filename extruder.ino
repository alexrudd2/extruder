// Extruder controller with small NEMA 17 stepper motor and A4988 driver

// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4; 
const int stopPin = 5;
const int forwardPin = 2;
const int reversePin = 1;
const int durationPin = A1;
const int speedPin = A2;
const int FORWARD = LOW;
const int REVERSE = HIGH;
const int MICROSTEPS = 16;
bool isRotating = false;
int speed = 30; // RPM
int duration = 5; // sec

void setup() {
  pinMode(stopPin, INPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(forwardPin, INPUT);
  pinMode(reversePin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
};
void rotate_for_duration(int direction, int speed, int duration);
void step(int direction);

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  // speed = 20 + 100 * (analogRead(speedPin) / 1023.0);
  duration = 5 + 115 * (analogRead(durationPin) / 1023.0);
  Serial.print(" D: ");
  Serial.println(duration);

  if (digitalRead(forwardPin) && !isRotating) rotate_for_duration(FORWARD, speed, duration);
  if (digitalRead(reversePin) && !isRotating) rotate_for_duration(REVERSE, 120, 10);
}

void rotate_for_duration(int direction, int speed, int duration) {
  // speed in RPM
  if (speed < 20) speed = 20;
  if (speed > 120) speed = 120;
  // duration in sec
  if (duration < 0) return;
  if (duration > 60) duration = 60;

  isRotating = true;
  unsigned long startTime = millis(); // Record the start time
  while (millis() - startTime < duration * 1000) {
    if (!(digitalRead(stopPin))) {
      isRotating = false;
      return;
    }
    step(direction);
    // 200 * MICROSTEPS steps per revolution
    delayMicroseconds(60 * 1000 * 1000 / speed / (200 * MICROSTEPS));
  }
  isRotating = false;
}

void step(int direction) {
  if (!(digitalRead(stopPin))) return;
  digitalWrite(dirPin, direction);
  digitalWrite(stepPin, HIGH);
  digitalWrite(stepPin, LOW);
}
// thanks to Dejan Nedelkovski, www.HowToMechatronics.com