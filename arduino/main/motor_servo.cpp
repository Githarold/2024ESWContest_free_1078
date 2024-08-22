// motor_servo.cpp

#include <Servo.h>
#include "motor_servo.h"

Servo myservo;  // 서보 모터 객체

void servo_up() {
  myservo.write(0);  // 서보를 0도로 회전
  delay(5000);       // 5초 대기
}

void servo_down() {
  myservo.write(60);  // 서보를 60도로 회전
  delay(7000);        // 7초 대기
}

void dispenser_activate() {
  servo_up();   // 서보를 올림
  servo_down(); // 서보를 내림
}
