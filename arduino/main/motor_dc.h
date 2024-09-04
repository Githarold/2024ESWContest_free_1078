// motor_dc.h

#ifndef DC_H
#define DC_H

#include <Arduino.h>

// 모터 제어에 필요한 핀 정의
extern const int END;  // 모터 활성화 핀
extern int IN7;        // 모터 입력 1
extern int IN8;        // 모터 입력 2

// 모터 제어 함수 선언
void dcMotorCW(int power, int time);       // 시계 방향 회전
void dcMotorCCW(int power, int time);      // 반시계 방향 회전
void stirCocktail(int power, int time, int count);  // 교차 회전

#endif
