// Extruder controller with small NEMA 17 stepper motor and A4988 driver

// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4; 
const int stopPin = 5;
const int forwardPin = 2;
const int reversePin = 1; // fixme
const int FORWARD = LOW;
const int REVERSE = HIGH;

void setup() {
  pinMode(stopPin, INPUT);
  pinMode(stepPin, OUTPUT); 
  pinMode(dirPin, OUTPUT);
  pinMode(forwardPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
};
void step(int direction, int speed);

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);

  // // clockwise
  // digitalWrite(dirPin, HIGH);
  // // Makes 200 * 16 pulses for making one full cycle rotation at 1/16 step
  // for(int x = 0; x < 3200; x++) {
  //   step(FORWARD, 30);
  // }
  // delay(1000); // One second delay
  // digitalWrite(LED_BUILTIN, LOW);
  
  // //counter-clockwise
  // // Makes 200 * 16 pulses for making two full cycle rotation at 1/16 step
  // for(int x = 0; x < 3200; x++) {
  //   step(REVERSE, 30);
  // }
  // delay(1000);
  if (digitalRead(stopPin)) {
    if (digitalRead(forwardPin)) step(FORWARD, 30);
  } 
}

void step(int direction, int speed) {
  digitalWrite(dirPin, direction);
  // 30 RPM = 625us per 1/16  step
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(125);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(500);
}
// thanks to Dejan Nedelkovski, www.HowToMechatronics.com