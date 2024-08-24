// motor_servo.h

#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>
#include <Servo.h>

extern Servo myservo;  // 서보 모터 객체 선언

// 함수 선언
void servo_up();           // 서보를 0도로 회전
void servo_down();         // 서보를 60도로 회전
void dispenser_activate(); // 디스펜서 활성화 (서보 업/다운)
void init_servo();
#endif
