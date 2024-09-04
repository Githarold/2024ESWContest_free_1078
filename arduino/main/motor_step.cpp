// motor_step.cpp

#include "motor_step.h"

// 모터 A와 B의 핀 설정 (역방향 구동을 위해 리스트로 설정)
const int ENA[2] = {2, 2}; 
int IN1[2] = {6, 3};       
int IN2[2] = {7, 4};       
const int ENB[2] = {5, 5}; 
int IN3[2] = {3, 6};       
int IN4[2] = {4, 7};       

// 소프트 스타트/스탑에 사용될 딜레이 값 배열
// 25개의 스텝에 대한 딜레이 값은 다음 식을 기반으로 계산됨: y = 49 * e^(-0.19 * x) + 4
// 여기서 x는 스텝 번호, y는 해당 스텝의 딜레이 (밀리초)
const int delays[] = {45, 38, 32, 27, 23, 20, 17, 15, 13, 11, 10, 9, 8, 7, 7, 6, 6, 6, 5, 5, 5, 5, 5, 5, 4};
int reverseDelays[sizeof(delays) / sizeof(int)];

// 모터 핀 모드 설정 및 초기화
void setupMotorPins(int motor) {
    
    pinMode(ENA[motor], OUTPUT);
    pinMode(IN1[motor], OUTPUT);
    pinMode(IN2[motor], OUTPUT);
    pinMode(ENB[motor], OUTPUT);
    pinMode(IN3[motor], OUTPUT);
    pinMode(IN4[motor], OUTPUT);
    digitalWrite(ENA[motor], LOW);
    digitalWrite(ENB[motor], LOW);
}

// 딜레이 배열을 역순으로 설정하는 함수
void setupReverseDelays() {
    
    for (int i = 0; i < sizeof(delays) / sizeof(int); i++) {
        reverseDelays[i] = delays[sizeof(delays) / sizeof(int) - 1 - i];
    }
}

// 모터 소프트 스타트 함수
void softStart(int motor) {
    
    for (int i = 0; i < sizeof(delays) / sizeof(delays[0]); i++) {
        stepMotorSoftStart(motor, delays[i]);
    }
}

// 모터 소프트 스탑 함수
void softStop(int motor) {
    
    for (int i = sizeof(delays) / sizeof(delays[0]) - 1; i >= 0; i--) {
        stepMotorSoftStart(motor, delays[i]);
    }
}

// 스텝모터 풀스텝 제어
void stepMotorSoftStart(int motor, int stepDelay) {
    
    digitalWrite(ENA[motor], HIGH);

    digitalWrite(IN1[motor], HIGH);
    digitalWrite(IN2[motor], LOW);
    digitalWrite(IN3[motor], HIGH);
    digitalWrite(IN4[motor], LOW);
    delay(stepDelay);

    digitalWrite(IN1[motor], HIGH);
    digitalWrite(IN2[motor], LOW);
    digitalWrite(IN3[motor], LOW);
    digitalWrite(IN4[motor], HIGH);
    delay(stepDelay);

    digitalWrite(IN1[motor], LOW);
    digitalWrite(IN2[motor], HIGH);
    digitalWrite(IN3[motor], LOW);
    digitalWrite(IN4[motor], HIGH);
    delay(stepDelay);

    digitalWrite(IN1[motor], LOW);
    digitalWrite(IN2[motor], HIGH);
    digitalWrite(IN3[motor], HIGH);
    digitalWrite(IN4[motor], LOW);
    delay(stepDelay);
}

// 추가 스텝 수행 (빠른 속도)
void stepMotorControl(int motor, int steps) {
    
    int d = 4;  
    for (int i = 0; i < steps; i++) {
        digitalWrite(IN1[motor], HIGH);
        digitalWrite(IN2[motor], LOW);
        digitalWrite(IN3[motor], HIGH);
        digitalWrite(IN4[motor], LOW);
        delay(d);

        digitalWrite(IN1[motor], HIGH);
        digitalWrite(IN2[motor], LOW);
        digitalWrite(IN3[motor], LOW);
        digitalWrite(IN4[motor], HIGH);
        delay(d);

        digitalWrite(IN1[motor], LOW);
        digitalWrite(IN2[motor], HIGH);
        digitalWrite(IN3[motor], LOW);
        digitalWrite(IN4[motor], HIGH);
        delay(d);

        digitalWrite(IN1[motor], LOW);
        digitalWrite(IN2[motor], HIGH);
        digitalWrite(IN3[motor], HIGH);
        digitalWrite(IN4[motor], LOW);
        delay(d);
    }
}

// 모터 비활성화시키는 함수
void disableMotor(int motor) {
    
    digitalWrite(ENA[motor], LOW);
    digitalWrite(ENB[motor], LOW);
    digitalWrite(IN1[motor], LOW);
    digitalWrite(IN2[motor], LOW);
    digitalWrite(IN3[motor], LOW);
    digitalWrite(IN4[motor], LOW);
}

// 디스크 회전 로직
// disk_step이 양수면 반시계방향, 음수면 시계방향으로 회전
// disk_step이 1이면 한바퀴, 2이면 두바퀴 회전
// 스텝 모터가 한 바퀴 회전하면 디스크는 다음 재료 위치로 이동
void diskRotate(int disk_step) {
    if (disk_step == 0) {
        return;  // 입력이 0이면 동작하지 않음
    }

    int motor = 0;
    if (disk_step > 0 && disk_step <= 7) {
        motor = 0;  // 반시계방향
        disk_step = disk_step - 1;
        digitalWrite(ENB[motor], HIGH);
    } else if (disk_step < 0 && disk_step >= -7) {
        motor = 1;  // 시계방향
        disk_step = disk_step + 1;
        digitalWrite(ENB[motor], HIGH);
    } else {
        return;  // 유효하지 않은 입력 값
    }

    softStart(motor);  // 모터 소프트 스타트
    stepMotorControl(motor, abs(disk_step) * 50);  // 디스크 회전
    softStop(motor);  // 모터 소프트 스탑
    disableMotor(motor);  // 모터 비활성화
}



// 초기 위치 설정용 디스크 회전 함수
void initRotate(int stepDelay) {
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                digitalWrite(IN1[1], HIGH);
                digitalWrite(IN2[1], LOW);
                digitalWrite(IN3[1], HIGH);
                digitalWrite(IN4[1], LOW);
                break;
            case 1:
                digitalWrite(IN1[1], HIGH);
                digitalWrite(IN2[1], LOW);
                digitalWrite(IN3[1], LOW);
                digitalWrite(IN4[1], HIGH);
                break;
            case 2:
                digitalWrite(IN1[1], LOW);
                digitalWrite(IN2[1], HIGH);
                digitalWrite(IN3[1], LOW);
                digitalWrite(IN4[1], HIGH);
                break;
            case 3:
                digitalWrite(IN1[1], LOW);
                digitalWrite(IN2[1], HIGH);
                digitalWrite(IN3[1], HIGH);
                digitalWrite(IN4[1], LOW);
                break;
        }
        
        delay(stepDelay);
        
    }
}

