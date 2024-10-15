// motor_step.cpp

#include "motor_step.h"

// AccelStepper 객체 생성 (DRIVER 모드 사용)
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// 마이크로스텝 해상도 설정 (A4988 기준)
const int MICROSTEPPING = 16; // 1/16 스텝

// 가속도 및 최대 속도 설정
float MAX_SPEED = 12800.0;         // 최대 속도: 9600 마이크로스텝/초
float ACCELERATION = 6400.0;    // 가속도: 28800 마이크로스텝/초²

// 이동할 총 스텝 수
long TOTAL_STEPS = 0;

// 초기 딜레이 (밀리초)
const unsigned long INITIAL_DELAY = 500;

// *** 마이크로스텝 해상도 설정 함수 ***
void setMicrostepping(int microstepping) {
    switch (microstepping) {
        case 1:  // Full Step
            digitalWrite(MS1_PIN, LOW);
            digitalWrite(MS2_PIN, LOW);
            digitalWrite(MS3_PIN, LOW);
            break;
        case 2:  // Half Step
            digitalWrite(MS1_PIN, HIGH);
            digitalWrite(MS2_PIN, LOW);
            digitalWrite(MS3_PIN, LOW);
            break;
        case 4:  // Quarter Step
            digitalWrite(MS1_PIN, LOW);
            digitalWrite(MS2_PIN, HIGH);
            digitalWrite(MS3_PIN, LOW);
            break;
        case 8:  // Eighth Step
            digitalWrite(MS1_PIN, HIGH);
            digitalWrite(MS2_PIN, HIGH);
            digitalWrite(MS3_PIN, LOW);
            break;
        case 16: // Sixteenth Step
            digitalWrite(MS1_PIN, HIGH);
            digitalWrite(MS2_PIN, HIGH);
            digitalWrite(MS3_PIN, HIGH);
            break;
        default: // Default to Full Step if invalid
            digitalWrite(MS1_PIN, LOW);
            digitalWrite(MS2_PIN, LOW);
            digitalWrite(MS3_PIN, LOW);
            break;
    }

}

// *** 스텝퍼를 움직이는 함수 ***
void moveStepper(long steps) {
    stepper.moveTo(stepper.currentPosition() + steps);
    
    // 목표 위치에 도달할 때까지 실행
    while (stepper.distanceToGo() != 0) {
        stepper.run();
    }
}

// *** 스텝퍼 초기 설정 함수 ***
void setupStepper() {
    digitalWrite(ENABLE_PIN, LOW);
    // 핀 모드 설정
    pinMode(MS1_PIN, OUTPUT);
    pinMode(MS2_PIN, OUTPUT);
    pinMode(MS3_PIN, OUTPUT);

    // 마이크로스텝 설정
    setMicrostepping(MICROSTEPPING);
    
    // AccelStepper 설정
    stepper.setMaxSpeed(MAX_SPEED);         // 최대 속도 설정
    stepper.setAcceleration(ACCELERATION);  // 가속도 설정
    
  
}

// *** 모터 비활성화 함수 ***
void disableMotor() {
    digitalWrite(ENABLE_PIN, HIGH); // 모터 비활성화
}

// *** 디스크 회전 함수 ***
void diskRotate(int disk_step) {
    // 입력이 0이면 동작하지 않음
    if (disk_step == 0) {
        return;
    }

    // 방향 설정: 양수면 시계 방향, 음수면 반시계 방향
    int direction = (disk_step > 0) ? -1 : 1;
    
    // 스텝 수 절대값으로 변환 (방향은 따로 설정되었으므로)
    long steps = abs(disk_step) * 3200;  // 6400은 모터의 한 바퀴당 스텝 수 조정 가능
    
    // 가속도 및 최대 속도 설정
    stepper.setMaxSpeed(MAX_SPEED);        // 최대 속도 설정
    stepper.setAcceleration(ACCELERATION); // 가속도 설정

    // 방향 설정 및 스텝퍼 움직이기
    moveStepper(direction * steps);  // 방향 곱해서 스텝 수 전달
}
