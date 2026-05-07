#include <SoftwareSerial.h>

// Bluetooth serial connection (RX, TX)
SoftwareSerial bluetooth(2, 3);

// Motor driver enable pins (speed control - PWM)
#define ENA 8   // Left motor speed
#define ENB 10  // Right motor speed

// Motor driver direction pins
#define IN1 5
#define IN2 4
#define IN3 6
#define IN4 7

// Speed value (0–255)
int speedValue = 150;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  // Set motor pins as output
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopCar();
  Serial.println("Robot Car Ready");
}

void loop() {
  if (bluetooth.available()) {
    Serial.println("Bluetooth connected");

    char command = bluetooth.read();
    Serial.println(command);

    switch (command) {
      case 'F': moveForward(); break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'S': stopCar(); break;
    }
  }
}

// -------- MOTOR FUNCTIONS --------

// Move forward
void moveForward() {
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Forward");
}

// Move backward
void moveBackward() {
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  Serial.println("Backward");
}

// Turn right
void turnRight() {
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Turn Right");
}

// Turn left
void turnLeft() {
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  Serial.println("Turn Left");
}

// Stop all motors
void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("Stop");
}
