#include "neopixel.h"

#define NUMPIXELS  24

void red(Adafruit_NeoPixel &strip) {
    // 모든 LED를 빨간색으로 설정
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(150, 0, 0)); // 빨간색으로 설정
    }
    strip.show(); // 모든 LED를 한 번에 켬
}

void blue(Adafruit_NeoPixel &strip) {
    // 모든 LED를 초록색으로 설정
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 150)); // 파란색으로 설정

    }
    strip.show(); // 모든 LED를 한 번에 켬

    delay(3000); // 3초 동안 켜진 상태 유지 (필요에 따라 시간 조정 가능)

    // 모든 LED를 끄기
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0)); // 모든 LED를 끔
    }
    strip.show(); // 업데이트하여 LED를 실제로 끔
}

void green(Adafruit_NeoPixel &strip) {
    // 모든 LED를 초록색으로 설정
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 150, 0)); // 초록색으로 설정
    }
    strip.show(); // 모든 LED를 한 번에 켬

    delay(1000); // 3초 동안 켜진 상태 유지 (필요에 따라 시간 조정 가능)

    // 모든 LED를 끄기
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0)); // 모든 LED를 끔
    }
    strip.show(); // 업데이트하여 LED를 실제로 끔
}



void white(Adafruit_NeoPixel &strip, int step, int totalSteps) {
    int pixelsToLight = (NUMPIXELS * step) / totalSteps;  // 켤 LED의 개수 계산
    for (int i = 0; i < pixelsToLight; i++) {
        int reverseIndex = NUMPIXELS - 1 - i;  // 반대 방향으로 인덱스 계산
        strip.setPixelColor(reverseIndex, strip.Color(150, 150, 150)); // 흰색으로 설정
    }
    strip.show(); // 모든 LED를 한 번에 켬
}



// LED 끄는 함수
void turnOffAllPixels(Adafruit_NeoPixel &strip) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0)); // 모든 LED를 끔
    }
    strip.show(); // 업데이트하여 LED를 실제로 끔
}

void purple(Adafruit_NeoPixel &strip) {
    // 모든 LED를 보라색으로 설정
    for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(75, 0, 130)); // 보라색으로 설정 (R=75, G=0, B=130)
    }
    strip.show(); // 모든 LED를 한 번에 켬
}
