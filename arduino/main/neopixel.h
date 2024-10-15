#ifndef NEOPIXEL
#define NEOPIXEL
#include <Adafruit_NeoPixel.h>
// 전체가 순차적으로 초록색으로 켜지는 함수
void red(Adafruit_NeoPixel &strip);
void blue(Adafruit_NeoPixel &strip);
void green(Adafruit_NeoPixel &strip);
void purple(Adafruit_NeoPixel &strip);
void white(Adafruit_NeoPixel &strip, int step, int totalSteps);
void turnOffAllPixels(Adafruit_NeoPixel &strip);
#endif // NEOPIXEL
