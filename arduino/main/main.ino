// main.ino

#include <Arduino.h>
// 모터 제어 라이브러리 포함
#include "motor_step.h"  
#include "motor_dc.h"    
#include "motor_servo.h" 


#define MAX_SIZE 10  // 명령 리스트의 최대 크기를 10으로 설정

int disk_rotate_list[MAX_SIZE];      // 디스크 회전 명령 리스트
int dispenser_push_list[MAX_SIZE];   // 디스펜서 푸시 명령 리스트
int listSize = 0;  // 현재 리스트에 저장된 명령의 개수

int dc_motor_state = 0;  // DC 모터의 상태를 저장하는 변수 (0: 정지, 1: 동작)
int endStopPin = 12;  // 엔드스탑 스위치가 연결된 핀
// 시리얼 통신, 모터 핀 설정 등 초기화 작업을 수행하는 함수
void setup() {

    Serial.begin(9600);  // 시리얼 통신을 9600 baud rate로 설정

    // 스텝 모터 핀 설정
    setupMotorPins(0);  
    setupMotorPins(1);  

    // 역방향 동작을 위한 딜레이 설정
    setupReverseDelays();  

    // DC 모터 핀 설정
    pinMode(END, OUTPUT);
    pinMode(IN7, OUTPUT);
    pinMode(IN8, OUTPUT);
    
    // endstop 핀 설정
    pinMode(endStopPin, INPUT);
    // 서보 모터 핀 설정
    initServo();
    myservo.detach();

    pinMode(11, OUTPUT);  // 서보 모터 핀을 OUTPUT으로 설정
    digitalWrite(11, LOW);  // 신호 핀을 LOW로 설정하여 잔류 전압 제거
    delay(300);
}

// 시리얼 데이터를 확인하고, 파싱하여 명령을 실행하는 메인함수
void loop() {

    initServo();
    myservo.detach();
    delay(300);
    // 시리얼 데이터를 확인하고 처리
    if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        
        parseData(data);  // 입력된 데이터를 파싱하여 명령 리스트에 저장
        initServo();

        // 컵의 초기위치 설정을 위해 initSetup()을 호출, endstop switch 작동 대기
        initSetup();

        initServo();
        
        // 리스트에 저장된 명령을 순차적으로 실행
        for (int i = 0; i < listSize; i++) {
            diskRotate(disk_rotate_list[i]);  // 디스크 회전
            delay(1000);  // 1초 대기
           
            for (int j = 0; j < dispenser_push_list[i]; j++) {
                dispenserActivate();  // 디스펜서 푸시
                delay(100);
                
            }
        }

        // DC 모터 상태가 1이면 모터를 동작시킴
        if (dc_motor_state == 1) {
            stirCocktail(127, 500, 3);  // 음료 혼합
            delay(500);  // 1초 대기
        }

        Serial.println("9");  // 완료 신호를 전송
        initServo();
    }
    
}

 // 입력된 문자열 데이터를 분석하여 명령 리스트를 구성하는 함수
void parseData(String data) {

    // 라즈베리파이로부터 받은 문자열의 첫 번째 부분을 잘라서 정수로 변환하여 DC 모터 상태로 저장
    int firstComma = data.indexOf(',');
    dc_motor_state = data.substring(0, firstComma).toInt();  


    // 리스트 초기화
    listSize = 0;
    memset(disk_rotate_list, 0, sizeof(disk_rotate_list));
    memset(dispenser_push_list, 0, sizeof(dispenser_push_list));
    
    // 각 대괄호의 위치를 찾음 
    int firstBracket = data.indexOf('[', firstComma);  
    int secondBracket = data.indexOf(']', firstBracket + 1);  
    int thirdBracket = data.indexOf('[', secondBracket + 1);  
    int lastBracket = data.indexOf(']', thirdBracket + 1);  

    // 디스크 회전 및 디스펜서 푸시 명령을 파싱하여 각각의 리스트에 저장하는 로직
    // 대괄호 안의 값을 추출하고, 쉼표를 기준으로 명령을 분리하여 리스트에 추가

    // 디스크 회전 명령 파싱
    String diskData = data.substring(firstBracket + 1, secondBracket);
    listSize = 0;  
    int startPos = 0;  
    int endPos = diskData.indexOf(',');

    while (endPos != -1) {  
        disk_rotate_list[listSize++] = diskData.substring(startPos, endPos).toInt();
        startPos = endPos + 1;
        endPos = diskData.indexOf(',', startPos);
    }
    disk_rotate_list[listSize++] = diskData.substring(startPos).toInt();  

    // 디스펜서 푸시 명령 파싱
    String dispenserData = data.substring(thirdBracket + 1, lastBracket);
    startPos = 0;  
    endPos = dispenserData.indexOf(',');
    int dispenserCount = 0;  

    while (endPos != -1) {
        dispenser_push_list[dispenserCount++] = dispenserData.substring(startPos, endPos).toInt();
        startPos = endPos + 1;
        endPos = dispenserData.indexOf(',', startPos);
    }
    dispenser_push_list[dispenserCount] = dispenserData.substring(startPos).toInt();  
}



void initSetup() {
    if (digitalRead(endStopPin) == LOW) {
        // 엔드스탑이 이미 눌려 있으면 아무 작업도 하지 않음
        return;
    } else {
        digitalWrite(ENA[1], HIGH);
        digitalWrite(ENB[1], HIGH);

        // 엔드스탑이 눌릴 때까지 계속 스텝 수행
        while (digitalRead(endStopPin) != LOW) {
            initRotate(15);
        }

        disableMotor(0);  // 모터 정지
    }
}
