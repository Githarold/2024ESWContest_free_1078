#include <Servo.h>
#include "servo.h"

Servo myservo;  // 서보 객체 생성



void servo_up() {
  // 서보를 0도로 회전
  myservo.write(0);
//  Serial.println("서보모터 위치: 0도");
  delay(5000);  // 5초 대기
}

void servo_down() {
  // 서보를 60도로 회전
  myservo.write(60);
//  Serial.println("서보모터 위치: 60도");
  delay(7000);  // 7초 대기
}

void dispenser_activate() {
  servo_up();
  servo_down();
}
