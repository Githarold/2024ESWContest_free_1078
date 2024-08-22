#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>
#include <Servo.h>

extern Servo myservo;  // 서보 객체 외부 선언

// 함수 선언
void servo_up();
void servo_down();
void dispenser_activate();

#endif
