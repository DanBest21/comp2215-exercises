/*
  image.h
  Defines various graphics for the game.
  Graphics are stored in program memory, and are
  in a simple (and inefficient) array of colours.
  Some images (the monster ones) use only half the pixels on the x
  axis and are then drawn bigger (duplicating each element in the array).
  TODO (when no more space): switch to palette images.
  
  Author: Giacomo Meanti
*/

#ifndef IMAGE_H
#define IMAGE_H
#include <avr/pgmspace.h>
#include <stdint.h>
#include "svgrgb565.h"

//27*11 = 297 * 2B = 594B
static uint16_t cannon_sprite[297] PROGMEM = {
    BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,
    GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,
    GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,
    GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,
    GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,
    GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,
    GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,
    GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN
};

//27*11 = 297 * 2B = 594B
static uint16_t cannon_sprite_2[297] PROGMEM = {
    BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,
    GREEN,BLACK,GREEN,BLACK,GREEN,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,GREEN,
    BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    GREEN,BLACK,GREEN,BLACK,GREEN,BLACK,GREEN,BLACK,GREEN,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,GREEN,BLACK,
    BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,
    BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,
    GREEN,BLACK,BLACK,GREEN,BLACK,GREEN,GREEN,BLACK,GREEN,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,GREEN,
    BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,GREEN,BLACK,BLACK,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,
    BLACK,BLACK,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,GREEN,BLACK
};

//27*11 = 297 * 2B = 594B
static uint16_t cannon_sprite_3[297] PROGMEM = {
    BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,
    BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,
    BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,
    BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,GREEN,BLACK,BLACK,BLACK,
    GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,GREEN,
    GREEN,GREEN,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,GREEN,BLACK,
    GREEN,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,GREEN,GREEN,BLACK,BLACK,GREEN,BLACK,BLACK,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK,BLACK,GREEN,BLACK,BLACK,
    GREEN,GREEN,BLACK,GREEN,BLACK,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,BLACK,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,GREEN,GREEN,BLACK,GREEN,BLACK,GREEN,BLACK
};

//9*8 = 72 * 2B = 144B
static uint16_t heart_sprite[72] PROGMEM = {
    BLACK,RED,RED,BLACK,BLACK,BLACK,RED,RED,BLACK,
    RED,RED,RED,RED,BLACK,RED,RED,RED,RED,
    RED,RED,RED,RED,RED,RED,RED,WHITE,RED,
    RED,RED,RED,RED,RED,RED,WHITE,RED,RED,
    BLACK,RED,RED,RED,RED,RED,RED,RED,BLACK,
    BLACK,BLACK,RED,RED,RED,RED,RED,BLACK,BLACK,
    BLACK,BLACK,BLACK,RED,RED,RED,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,RED,BLACK,BLACK,BLACK,BLACK
};

//16x14
static uint16_t astro_sprite[] PROGMEM = {
    BLACK,BLACK,BLACK,BLACK,BLACK,RED,RED,RED,RED,RED,RED,DARK_RED,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,BLACK,RED,RED,RED,RED,RED,RED,DARK_RED,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,DARK_RED,BLACK,BLACK,
    BLACK,BLACK,BLACK,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,DARK_RED,BLACK,BLACK,
    BLACK,BLACK,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,DARK_RED,BLACK,
    BLACK,BLACK,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,DARK_RED,BLACK,
    BLACK,RED,RED,BLACK,RED,RED,BLACK,RED,RED,BLACK,RED,RED,BLACK,RED,RED,DARK_RED,
    BLACK,RED,RED,BLACK,RED,RED,BLACK,RED,RED,BLACK,RED,RED,BLACK,RED,RED,DARK_RED,
    RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,
    RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,RED,
    BLACK,BLACK,RED,RED,RED,DARK_RED,BLACK,RED,RED,DARK_RED,BLACK,RED,RED,RED,DARK_RED,BLACK,
    BLACK,BLACK,RED,RED,RED,DARK_RED,BLACK,RED,RED,DARK_RED,BLACK,RED,RED,RED,DARK_RED,BLACK,
    BLACK,BLACK,BLACK,RED,DARK_RED,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,RED,DARK_RED,BLACK,BLACK,
    BLACK,BLACK,BLACK,RED,DARK_RED,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,RED,DARK_RED,BLACK,BLACK
};

//13x8 = 104 * 2B = 208B
static uint16_t monster_sprite_1A[] PROGMEM = {
    BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,
};
//13x8 = 104 * 2B = 208B
static uint16_t monster_sprite_1B[] PROGMEM = {
    BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,WHITE,BLACK,BLACK,BLACK
};
//13x8 = 104 * 2B = 208B
static uint16_t monster_sprite_2A[416] PROGMEM = {
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,
    BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    BLACK,WHITE,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,BLACK,
    BLACK,WHITE,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,BLACK,
    BLACK,WHITE,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,WHITE,BLACK,
    BLACK,WHITE,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,WHITE,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK
};
//13x8 = 104 * 2B = 208B
static uint16_t monster_sprite_2B[416] PROGMEM = {
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,
    BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,
    BLACK,WHITE,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,BLACK,
    BLACK,WHITE,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,BLACK,
    BLACK,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,WHITE,BLACK,
    BLACK,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,WHITE,BLACK,
    BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,
    BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK
};
//13x8 = 104 * 2B = 208B
static uint16_t monster_sprite_3A[] PROGMEM = {
    BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,
    BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,
    WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    WHITE,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,WHITE,BLACK,
    WHITE,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,WHITE,BLACK,
    WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    BLACK,BLACK,WHITE,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,
    BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK
};
//13x8 = 104 * 2B = 208B
static uint16_t monster_sprite_3B[] PROGMEM = {
    BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,
    BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,
    WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    WHITE,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,WHITE,BLACK,
    WHITE,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,WHITE,BLACK,
    WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,
    BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,
    WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,
    WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK
};
//13x8 = 104 * 2B = 208B
static uint16_t monster_sprite_exp[416] PROGMEM = {
    BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,
    BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,
    BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,
    BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,
    WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,
    BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,
    BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,
    BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,
    BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,BLACK,BLACK,WHITE,BLACK,BLACK,WHITE,BLACK,
    BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,
    BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK
};

//4x9
static uint16_t triangle_sprite[28] PROGMEM = {
    BLUE,BLACK,BLACK,BLACK,
    BLUE,BLUE,BLACK,BLACK,
    BLUE,BLUE,BLUE,BLACK,
    BLUE,BLUE,BLUE,BLUE,
    BLUE,BLUE,BLUE,BLACK,
    BLUE,BLUE,BLACK,BLACK,
    BLUE,BLACK,BLACK,BLACK,
};
#endif /* IMAGE_H */
/*
  Copyright 2015 Giacomo Meanti
  At your option this work is licensed under a Creative Commons
  Attribution-NonCommercial 3.0 Unported License [1], or under a
  Creative Commons Attribution-ShareAlike 3.0 Unported License [2].
  [1]: See: http://creativecommons.org/licenses/by-nc/3.0/
  [2]: See: http://creativecommons.org/licenses/by-sa/3.0/
  =================================================================
*/