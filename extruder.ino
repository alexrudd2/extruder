// Extruder controller with small NEMA 17 stepper motor and A4988 driver

// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4; 
const int stopPin = 5;
const int forwardPin = 2;
const int reversePin = 1;
const int FORWARD = LOW;
const int REVERSE = HIGH;
const int MICROSTEPS = 16;

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

  if (digitalRead(forwardPin)) rotate_for_duration(FORWARD, 30, 5);
  if (digitalRead(reversePin)) rotate_for_duration(REVERSE, 120, 10);
}

void rotate_for_duration(int direction, int speed, int duration) {
  // speed in RPM
  if (speed < 20) speed = 20;
  if (speed > 60) speed = 60;
  // duration in sec
  if (duration < 0) return;
  if (duration > 60) duration = 60;

  unsigned long startTime = millis(); // Record the start time
  while (millis() - startTime < duration * 1000) {
    if (!(digitalRead(stopPin))) return;
    step(direction);
    // 200 * MICROSTEPS steps per revolution
    delayMicroseconds(60 * 1000 * 1000 / speed / (200 * MICROSTEPS));
  }
}

void step(int direction) {
  if (!(digitalRead(stopPin))) return;
  digitalWrite(dirPin, direction);
  digitalWrite(stepPin, HIGH);
  digitalWrite(stepPin, LOW);
}
// thanks to Dejan Nedelkovski, www.HowToMechatronics.com