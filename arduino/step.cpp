// step.cpp
#include "step.h"

const int ENA[2] = {2, 2}; // 모터 A와 B의 활성화 핀
int IN1[2] = {3, 6};       // 모터 A와 B의 입력 1
int IN2[2] = {4, 7};       // 모터 A와 B의 입력 2
const int ENB[2] = {5, 5}; // 모터 A와 B의 활성화 핀
int IN3[2] = {6, 3};       // 모터 A와 B의 입력 3
int IN4[2] = {7, 4};       // 모터 A와 B의 입력 4

const int delays[] = {45, 38, 32, 27, 23, 20, 17, 15, 13, 11, 10, 9, 8, 7, 7, 6, 6, 6, 5, 5, 5, 5, 5, 5, 4};
int reverseDelays[sizeof(delays) / sizeof(int)];

void setupMotorPins(int motor) {
    pinMode(ENA[motor], OUTPUT);
    pinMode(IN1[motor], OUTPUT);
    pinMode(IN2[motor], OUTPUT);
    pinMode(ENB[motor], OUTPUT);
    pinMode(IN3[motor], OUTPUT);
    pinMode(IN4[motor], OUTPUT);

    // 초기화 시 모터를 비활성화 상태로 설정
    digitalWrite(ENA[motor], LOW);
    digitalWrite(ENB[motor], LOW);
}

void setupReverseDelays() {
    for (int i = 0; i < sizeof(delays) / sizeof(int); i++) {
        reverseDelays[i] = delays[sizeof(delays) / sizeof(int) - 1 - i];
    }
}

void performSteps(int motor, const int delayArray[]) {
    for (int i = 0; i < sizeof(delays) / sizeof(int); i++) {
        stepMotorSoftStart(motor, delayArray[i]);
    }
}

void softStart(int motor) {
    for (int i = 0; i < sizeof(delays) / sizeof(delays[0]); i++) {
        stepMotorSoftStart(motor, delays[i]);
    }
}

void softStop(int motor) {
    for (int i = sizeof(delays) / sizeof(delays[0]) - 1; i >= 0; i--) {
        stepMotorSoftStart(motor, delays[i]);
    }
}

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

void performAdditionalSteps(int motor, int steps) {
    int d = 4;  // 빠른 스텝을 위한 작은 딜레이
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

void disableMotor(int motor) {
    digitalWrite(ENA[motor], LOW);  // 모터 비활성화
    digitalWrite(ENB[motor], LOW);  // 모터 비활성화

    digitalWrite(IN1[motor], LOW);  // 모든 입력 핀을 LOW로 설정
    digitalWrite(IN2[motor], LOW);
    digitalWrite(IN3[motor], LOW);
    digitalWrite(IN4[motor], LOW);
}

void disk_rotate(int disk_step) {
    if (disk_step == 0) {
        // 입력 값이 0인 경우, 아무 동작도 하지 않습니다.
        return;
    }

    int motor = 0;
    if (disk_step > 0 && disk_step <= 7) {
        // 반시계방향 회전 처리
        motor = 0;
        disk_step = disk_step - 1;
        digitalWrite(ENB[motor], HIGH); // 반시계방향 활성화
    } else if (disk_step < 0 && disk_step >= -7) {
        // 시계방향 회전 처리
        motor = 1;
        disk_step = disk_step + 1;
        digitalWrite(ENB[motor], HIGH); // 시계방향 활성화
    } else {
        // 유효하지 않은 입력일 경우 아무 작업도 수행하지 않음
        return;
    }

    // 모터 동작 수행
    softStart(motor);
    performAdditionalSteps(motor, abs(disk_step) * 50);
    softStop(motor);

    // 모터 비활성화
    disableMotor(motor);
}








////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int endStopPin = 12;  // 엔드스탑 스위치를 연결한 핀 (12번 핀)
int endStopState = 0;       // 현재 엔드스탑 상태
int lastEndStopState = 0;   // 이전 엔드스탑 상태
unsigned long lastDebounceTime = 0;  // 마지막 디바운싱 체크 시간
unsigned long debounceDelay = 50;    // 디바운싱을 위한 지연 시간 (밀리초 단위)

void setupEndStop() {
    pinMode(endStopPin, INPUT);  // 엔드스탑 핀을 입력으로 설정
}

bool isEndStopTriggered() {
    int reading = digitalRead(endStopPin);

    // 스위치 상태가 바뀌었는지 확인
    if (reading != lastEndStopState) {
        lastDebounceTime = millis();  // 상태 변화 시 시간 기록
    }

    // 디바운싱 시간 동안의 상태가 안정되었는지 확인
    if ((millis() - lastDebounceTime) > debounceDelay) {
        // 상태가 안정되면 현재 읽은 상태를 반영
        if (reading != endStopState) {
            endStopState = reading;

            // 스위치가 LOW로 눌렸을 때 트리거됨
            if (endStopState == LOW) {
                lastEndStopState = reading;  // 상태 업데이트
                return true;
            }
        }
    }

    lastEndStopState = reading;  // 상태 업데이트
    return false;  // 엔드스탑 트리거되지 않음
}

void halfstep_thermo(int stepDelay) {
    // 하프 스텝 모드에서 전류를 최적화하여 발열을 줄임
    for (int i = 0; i < 8; i++) {
        // 각 스텝에 따라 전류 조절
        digitalWrite(IN1[1], i == 0 || i == 1 || i == 2 || i == 3 ? HIGH : LOW);
        digitalWrite(IN2[1], i == 5 || i == 6 || i == 7 || i == 0 ? HIGH : LOW);
        digitalWrite(IN3[1], i == 0 || i == 7 || i == 6 || i == 4 ? HIGH : LOW);
        digitalWrite(IN4[1], i == 3 || i == 4 || i == 5 || i == 2 ? HIGH : LOW);
        
        delay(stepDelay);
        
        // 전류 감소를 위한 딜레이
        digitalWrite(IN1[1], LOW);
        digitalWrite(IN2[1], LOW);
        digitalWrite(IN3[1], LOW);
        digitalWrite(IN4[1], LOW);
        delay(stepDelay / 2);
    }
}

void waitForEndStop() {
    digitalWrite(ENA[1], HIGH);
    digitalWrite(ENB[1], HIGH);

    // 엔드스탑이 눌릴 때까지 추가적인 스텝을 수행
    while (!isEndStopTriggered()) {
        halfstep_thermo(30);
    }

    // 엔드스탑이 트리거되었으면 모터를 정지
    disableMotor(0);
}
