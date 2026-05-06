// ----------- HC-SR04 PINS -----------
#define trigPin A4
#define echoPin A5

// ----------- MOTORS -----------
// Right motor group
#define rightMotorDir1 4
#define rightMotorDir2 5
#define rightMotorPWM 3

// Left motor group
#define leftMotorDir1 7
#define leftMotorDir2 6
#define leftMotorPWM 10

int speedValue = 120;        // Motor speed (0–255)
int distanceThreshold = 20;  // Distance threshold (cm)

// ----------- SETUP -----------
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(rightMotorDir1, OUTPUT);
  pinMode(rightMotorDir2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);

  pinMode(leftMotorDir1, OUTPUT);
  pinMode(leftMotorDir2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);

  Serial.begin(9600);

  // Initialize randomness
  randomSeed(analogRead(0));

  Serial.println("Obstacle Avoiding Robot Started");
}

// ----------- LOOP -----------
void loop() {

  int distance = measureDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > distanceThreshold) {
    moveForward();
  } else {
    stopMotors();
    delay(200);

    moveBackward();
    delay(300);

    stopMotors();
    delay(200);

    // Random direction selection
    if (random(0, 2) == 0) {
      turnLeft();
    } else {
      turnRight();
    }

    delay(400);
  }

  delay(50);
}

// ----------- DISTANCE MEASUREMENT -----------

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) return 999;

  int distance = duration * 0.034 / 2;
  return distance;
}

// ----------- MOVEMENT FUNCTIONS -----------

void moveForward() {
  digitalWrite(rightMotorDir1, HIGH);
  digitalWrite(rightMotorDir2, LOW);
  analogWrite(rightMotorPWM, speedValue);

  digitalWrite(leftMotorDir1, HIGH);
  digitalWrite(leftMotorDir2, LOW);
  analogWrite(leftMotorPWM, speedValue);
}

void moveBackward() {
  digitalWrite(rightMotorDir1, LOW);
  digitalWrite(rightMotorDir2, HIGH);
  analogWrite(rightMotorPWM, speedValue);

  digitalWrite(leftMotorDir1, LOW);
  digitalWrite(leftMotorDir2, HIGH);
  analogWrite(leftMotorPWM, speedValue);
}

void turnRight() {
  digitalWrite(rightMotorDir1, LOW);
  digitalWrite(rightMotorDir2, HIGH);
  analogWrite(rightMotorPWM, speedValue);

  digitalWrite(leftMotorDir1, HIGH);
  digitalWrite(leftMotorDir2, LOW);
  analogWrite(leftMotorPWM, speedValue);
}

void turnLeft() {
  digitalWrite(rightMotorDir1, HIGH);
  digitalWrite(rightMotorDir2, LOW);
  analogWrite(rightMotorPWM, speedValue);

  digitalWrite(leftMotorDir1, LOW);
  digitalWrite(leftMotorDir2, HIGH);
  analogWrite(leftMotorPWM, speedValue);
}

void stopMotors() {
  analogWrite(rightMotorPWM, 0);
  analogWrite(leftMotorPWM, 0);
}
