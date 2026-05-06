// ----------- SENSOR DEFINITIONS -----------
#define SensorLeft A1
#define SensorCenter A2
#define SensorRight A3

// ----------- MOTOR DEFINITIONS -----------
// Right motor group (front + rear)
#define MotorR1 4
#define MotorR2 5
#define MotorR3 3  // PWM pin

// Left motor group (front + rear)
#define MotorL1 7
#define MotorL2 6
#define MotorL3 10 // PWM pin

int speedVal = 75;

// ----------- SETUP -----------
void setup() {
  pinMode(SensorLeft, INPUT);
  pinMode(SensorCenter, INPUT);
  pinMode(SensorRight, INPUT);

  Serial.begin(9600);
  Serial.println("Line follower started");
  delay(2000);

  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorR3, OUTPUT);

  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorL3, OUTPUT);
}

// ----------- LOOP -----------
void loop() {

  int left = digitalRead(SensorLeft);
  int center = digitalRead(SensorCenter);
  int right = digitalRead(SensorRight);

  // ----------- SERIAL DEBUG -----------
  Serial.print("Left: ");
  Serial.print(left);
  Serial.print(" Center: ");
  Serial.print(center);
  Serial.print(" Right: ");
  Serial.print(right);
  Serial.print(" -> ");

  if (left == 0 && center == 0 && right == 0) {
    Serial.println("BLACK");
  }
  else if (left == 1 && center == 1 && right == 1) {
    Serial.println("WHITE");
  }
  else {
    Serial.println("MIXED");
  }

  delay(100);

  // ----------- LINE FOLLOWING LOGIC -----------
  if (left == 0 && center == 1 && right == 0) {
    forward();
  }
  else if (left == 0 && center == 0 && right == 1) {
    turnRight();
  }
  else if (left == 1 && center == 0 && right == 0) {
    turnLeft();
  }
  else if (left == 1 && center == 1 && right == 1) {
    stopMotors();
  }
  else {
    stopMotors();
  }
}

// ----------- MOVEMENT FUNCTIONS -----------

void forward() {
  // Right motors
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorR3, speedVal);

  // Left motors
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorL3, speedVal);
}

void turnRight() {
  // Right motors (slower)
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorR3, 50);

  // Left motors (faster)
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorL3, speedVal);
}

void turnLeft() {
  // Right motors (faster)
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorR3, speedVal);

  // Left motors (slower)
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorL3, 50);
}

void stopMotors() {
  analogWrite(MotorR3, 0);
  analogWrite(MotorL3, 0);
}
