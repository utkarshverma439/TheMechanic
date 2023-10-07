#include <Servo.h>
Servo Myservo;
#define trigPin 9           // Trig Pin Of HC-SR04
#define echoPin 8           // Echo Pin Of HC-SR04
#define MLa 4                // left motor 1st pin
#define MLb 5                // left motor 2nd pin
#define MRa 6                // right motor 1st pin
#define MRb 7                // right motor 2nd pin
long duration, distance;
int obstacleCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(MLa, OUTPUT);     // Set Motor Pins As O/P
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);
  pinMode(trigPin, OUTPUT); // Set Trig Pin As O/P To Transmit Waves
  pinMode(echoPin, INPUT);  // Set Echo Pin As I/P To Receive Reflected Waves
  Myservo.attach(10);
}

void loop() {
  Serial.begin(9600);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);       // Transmit Waves For 10us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);  // Receive Reflected Waves
  distance = duration / 58.2;        // Get Distance
  Serial.println(distance);
  delay(50);  // Increase the delay to slow down the loop

  if (distance <= 15 && distance > 0) {
    // An obstacle is detected
    obstacleCount++;
    digitalWrite(MRb, LOW);     // Stop
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, LOW);
    delay(500);  // Delay to stop the motors

    Myservo.write(0);
    delay(1000);  // Delay for servo movement
    Myservo.write(180);
    delay(1000);  // Delay for servo movement
    Myservo.write(90);
    delay(1000);  // Delay for servo movement

    digitalWrite(MRb, LOW);     // Move Backward
    digitalWrite(MRa, HIGH);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, HIGH);
    delay(1000);  // Delay for backward movement

    digitalWrite(MRb, LOW);        // Stop
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, LOW);
    delay(500);  // Delay to stop the motors

    if (obstacleCount % 2 == 0) {
      // Even number of obstacles, turn right
      digitalWrite(MRb, HIGH);     // Turn Right
      digitalWrite(MRa, LOW);
      digitalWrite(MLa, LOW);
      digitalWrite(MLb, HIGH);
      delay(1000);  // Delay for right turn
    } else {
      // Odd number of obstacles, turn left
      digitalWrite(MRb, LOW);      // Turn Left
      digitalWrite(MRa, LOW);
      digitalWrite(MLa, LOW);
      digitalWrite(MLb, HIGH);
      delay(1000);  // Delay for left turn
    }
  } else {
    // No obstacle, move forward
    digitalWrite(MRb, HIGH);        // Move Forward
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, HIGH);
    digitalWrite(MLa, LOW);
  }
}
