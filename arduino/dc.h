//dc.h

#ifndef DC_H
#define DC_H

#include <Arduino.h>

extern const int END;
extern int IN7;
extern int IN8;



void dc_cw(int power, int time);
void dc_ccw(int power, int time);
void stir(int power, int time, int count);


#endif
