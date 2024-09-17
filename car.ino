#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the CE and CSN pins
#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

// Define motor control pins
#define IN1 4
#define IN2 5
#define ENA 3 // PWM-capable pin
#define IN3 8
#define IN4 7
#define ENB 6 // PWM-capable pin

// Motor speed variable
int motorSpeedA = 200;
int motorSpeedB = 200;

void setup() {
  Serial.begin(9600);

  if (!radio.begin()) {
    Serial.println("Radio initialization failed");
    while (1);
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ensure motors are stopped initially
  stopMotors();
}

void loop() {
  if (radio.available()) {
    char command;
    radio.read(&command, sizeof(command));

    // Print the received command to the Serial Monitor
    Serial.print("Received command: ");
    Serial.println(command);

    switch (command) {
      case 'F': // Forward
        moveForward();
        break;
      case 'B': // Backward
        moveBackward();
        break;
      case 'L': // Left
        turnLeft();
        break;
      case 'R': // Right
        turnRight();
        break;
      case 'P': // Spin (pivot)
        spin();
        break;
      case 'S': // Stop
        stopMotors();
        break;
    }
  }
}

void moveForward() {
  analogWrite(ENA, motorSpeedA); // Enable Motor A at defined speed
  analogWrite(ENB, motorSpeedB); // Enable Motor B at defined speed

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(1000); // Move forward for 1 second
}

void moveBackward() {
  analogWrite(ENA, motorSpeedA); // Enable Motor A at defined speed
  analogWrite(ENB, motorSpeedB); // Enable Motor B at defined speed

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(1000); // Move backward for 1 second
}

void turnRight() {
  analogWrite(ENA, motorSpeedA); // Enable Motor A at defined speed
  analogWrite(ENB, motorSpeedB); // Enable Motor B at defined speed

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(1000); // Turn right for 1 second
}

void turnLeft() {
  analogWrite(ENA, motorSpeedA); // Enable Motor A at defined speed
  analogWrite(ENB, motorSpeedB); // Enable Motor B at defined speed

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(1000); // Turn left for 1 second
}

void spin() {
  analogWrite(ENA, motorSpeedA); // Enable Motor A at defined speed
  analogWrite(ENB, motorSpeedB); // Enable Motor B at defined speed

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(1000); // Spin right for 1 second
}

void stopMotors() {
  analogWrite(ENA, 0); // Disable Motor A
  analogWrite(ENB, 0); // Disable Motor B

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
