#include <Servo.h>

Servo servo1;
Servo servo2;

const int echoPin1 = 9;
const int trigPin1 = 8; 
const int echoPin2 = 6;
const int trigPin2 = 5;

float duration1, distance1, duration2, distance2;
int lock = 0;

void pickServo() {
  Serial.println("In pickServo()");
  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.print(" cm, Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  if (duration1 <= duration2) {
    liftServo1();
  } else {
    liftServo2();
  }
}

void liftServo1() {
  Serial.println("In liftServo1()");
  if (lock != 0) return;

  lock = 1;
  while (distance1 < 7) {
    Serial.println("Object detected near Sensor 1. Moving Servo 1.");
    servo1.write(90);
    delay(3000);
    GetDistance1();
  }
  servo1.write(180);
  delay(50);
  lock = 0;
}

void liftServo2() {
  Serial.println("In liftServo2()");
  if (lock != 0) return;

  lock = 1;
  while (distance2 < 7) {
    Serial.println("Object detected near Sensor 2. Moving Servo 2.");
    servo2.write(90);
    delay(3000);
    GetDistance2();
  }
  servo2.write(360);
  delay(200);
  lock = 0;
}

void setup() {
  pinMode(trigPin1, OUTPUT);  
  pinMode(echoPin1, INPUT);  
  pinMode(trigPin2, OUTPUT);  
  pinMode(echoPin2, INPUT);  

  Serial.begin(9600);  

  servo1.attach(3);
  servo2.attach(4);
}
void GetDistance1(){
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 * 0.0343) / 2;
}

void GetDistance2(){
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 * 0.0343) / 2;
}
void loop() {
  GetDistance1();
  GetDistance2();
 
  delay(50);
  pickServo();
}
