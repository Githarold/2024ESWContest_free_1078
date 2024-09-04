// motor_servo.cpp

#include <Servo.h>
#include "motor_servo.h"

Servo myservo;  // 서보 모터 객체

void servoArmUp() {
  myservo.write(0);  // 서보를 0도로 회전
  delay(3000);       // 5초 대기
}

void servoArmDown() {
  myservo.write(50);  // 서보를 60도로 회전
  delay(3000);        // 7초 대기
}

void dispenserActivate() {
  myservo.attach(11);
  delay(100);
  servoArmUp();   // 서보를 올림
  servoArmDown(); // 서보를 내림
  myservo.detach();
  delay(300);
}

void initServo() {
  myservo.attach(11);
  delay(100);
  myservo.write(50);  // 서보를 60도로 회전
  delay(1000);        
  myservo.detach();
  delay(300);
}
