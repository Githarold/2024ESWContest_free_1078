// motor_step.h

#ifndef MOTOR_STEP_H
#define MOTOR_STEP_H

#include <AccelStepper.h>
#include <Arduino.h>

// 핀 정의
#define DIR_PIN 30    // 방향 핀
#define STEP_PIN 31   // 스텝 핀
#define MS1_PIN 32    // 마이크로스텝 설정 핀1
#define MS2_PIN 33    // 마이크로스텝 설정 핀2
#define MS3_PIN 34    // 마이크로스텝 설정 핀3
#define ENABLE_PIN 35 // 모터 활성화/비활성화 핀

// 마이크로스텝 해상도 (A4988 기준)
extern const int MICROSTEPPING;

// 최대 속도 및 가속도 설정
extern float MAX_SPEED;
extern float ACCELERATION;

// 이동할 총 스텝 수
extern long TOTAL_STEPS;

// 초기 딜레이 (밀리초)
extern const unsigned long INITIAL_DELAY;

// AccelStepper 객체 선언
extern AccelStepper stepper;

// 함수 선언

// 마이크로스텝 해상도 설정 함수
void setMicrostepping(int microstepping);

// 스텝퍼를 움직이는 함수
void moveStepper(long steps);

// 스텝퍼 초기 설정 함수
void setupStepper();

// 모터 비활성화 함수
void disableMotor();

// 디스크 회전 함수
void diskRotate(int disk_step);

void runMotorOneWay();



#endif // MOTOR_STEP_H
