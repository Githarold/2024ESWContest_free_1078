// motor_dc.cpp

#include <Arduino.h>
#include "motor_dc.h"

// 핀 정의
const int END = 9;   // 모터 활성화 핀 (PWM 가능)
int IN7 = 10;   // 모터 입력 1
int IN8 = 8;  // 모터 입력 2

//dc모터 시계방향 회전 함수
void dcMotorCW(int power, int time) {
    // 모터 초기화
    digitalWrite(END, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);

    //터 속도 증가(소프트 스타트)
    for (int speed = 0; speed <= power; speed++) {
        analogWrite(END, speed);
        delay(10);
    }

    // 모터 시계 방향 회전
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, LOW);
    analogWrite(END, power);
    delay(time);

    // 모터 속도 감소(소프트 스탑)
    for (int speed = power; speed >= 0; speed--) {
        analogWrite(END, speed);
        delay(10);
    }
}

//dc모터 반시계방향 회전 함수
void dcMotorCCW(int power, int time) {
    // 모터 초기화 및 속도 증가(소프트 스타트)
    digitalWrite(END, LOW);
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, LOW);

    for (int speed = 0; speed <= power; speed++) {
        analogWrite(END, speed);
        delay(10);
    }

    // 모터 반시계 방향 회전
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, HIGH);
    analogWrite(END, power);
    delay(time);

    // 모터 속도 감소
    for (int speed = power; speed >= 0; speed--) {
        analogWrite(END, speed);
        delay(10);
    }
}

void stirCocktail(int power, int time, int count) {
    // 주어진 횟수만큼 시계 방향 및 반시계 방향 회전 반복
    for (int i = 0; i < count; i++) {
        dcMotorCW(power, time);
        dcMotorCCW(power, time);
    }
    dcMotorCW(0, 2000);  // 모터 정지
}
