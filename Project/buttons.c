//
// Created by platelminto on 2/11/20.
// Is one of the buttons pressed (only triggers once per press)

#include <avr/io.h>
#include "lib/rotary/rotary.h"

int up_pressed = 0;
int right_pressed = 0;
int down_pressed = 0;
int left_pressed = 0;

int is_up_pressed() {
    if (!up_pressed && !((PINC >> SWN) & 1)) {
        up_pressed = 1;
        return 1;
    } else if (!((PINC >> SWN) & 1)) {
        return 0;
    } else {
        up_pressed = 0;
        return 0;
    }
}

int is_right_pressed() {
    if (!right_pressed && !((PINC >> SWE) & 1)) {
        right_pressed = 1;
        return 1;
    } else if (!((PINC >> SWE) & 1)) {
        return 0;
    } else {
        right_pressed = 0;
        return 0;
    }
}

int is_down_pressed() {
    if (!down_pressed && !((PINC >> SWS) & 1)) {
        down_pressed = 1;
        return 1;
    } else if (!((PINC >> SWS) & 1)) {
        return 0;
    } else {
        down_pressed = 0;
        return 0;
    }
}

int is_left_pressed() {
    if (!left_pressed && !((PINC >> SWW) & 1)) {
        left_pressed = 1;
        return 1;
    } else if (!((PINC >> SWW) & 1)) {
        return 0;
    } else {
        left_pressed = 0;
        return 0;
    }
}