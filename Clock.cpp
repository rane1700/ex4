//
// Created by shani on 12/27/16.
//

#include "Clock.h"
Clock::Clock() {
    time = 0;
}
void Clock::incTime() { time++; }
int Clock::getTime() { return time;}