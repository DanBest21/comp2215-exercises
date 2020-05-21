/* Configure I/O Ports */

/* For La Fortuna board

   | Port | Pin | Function         |
   |------+-----+------------------|
   | C    |   2 | Up Button        |
   | C    |   3 | Right Button     |
   | C    |   4 | Down Button      |
   | C    |   5 | Left Button      |

*/

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <time.h>
#include <stdlib.h>
#include "lib/lcd/lcd.h"
#include "lib/rotary/rotary.h"
#include "buttons.h"
#include "main.h"

typedef int bool;

#define FPS 10
#define SCREEN_WIDTH 320
#define DIFFICULTY_TIMER 10000
#define SCREEN_HEIGHT 240
#define CRAB_WIDTH 50
#define CRAB_HEIGHT 40
#define TURTLE_WIDTH 35
#define TURTLE_HEIGHT 50
#define BOTTOM_GAP 10
#define MAX_TURTLES 5 * 6
#define MAX_BOLTS 2 * 6
#define TRUE  1
#define FALSE 0

struct turtle {uint8_t x; uint16_t y; bool lastRight;};
struct bolt {uint8_t x; uint8_t size; uint8_t tick;};

volatile uint16_t difficulty = 1;
volatile uint16_t score = 0;
volatile uint16_t lives = 3;
volatile uint8_t tick = 0;
volatile uint8_t tick2 = 0;
volatile uint8_t tick3 = 0;
volatile uint8_t position = 0;
volatile struct turtle turtles[MAX_TURTLES];
volatile struct bolt bolts[MAX_BOLTS];
volatile uint16_t activeTurtles = 0;
volatile uint16_t activeBolts = 0;
volatile uint16_t timeElapsedSinceLevelUp = 0;
volatile int finished = FALSE;
volatile bool damaged = FALSE;

void init(void) {

    /* 8MHz clock, no prescaling (DS, p. 48) */
    CLKPR = (1 << CLKPCE);
    CLKPR = 0;

    init_lcd();

    set_frame_rate_hz(61);
    /* Enable tearing interrupt to get flicker free display */
    EIMSK |= _BV(INT6);

    /* Set as input */
    DDRC &= ~_BV(SWN) & ~_BV(SWE) & ~_BV(SWS) & ~_BV(SWW);
    /* Enable direction buttons */
    PORTC |= _BV(SWN) | _BV(SWE) | _BV(SWS) | _BV(SWW);

    /* Timer 0 for button listening interrupt: */
    TCCR0A = _BV(WGM01);
    TCCR0B = _BV(CS02) | _BV(CS00); /* F_CPU / 1024 */

    /* Timer 3 (16-bit) for frame counting */
    TCCR3A = 0;
    TCCR3B |= _BV(WGM32);
    TCCR3B |= _BV(CS32) | _BV(CS30); /* F_CPU / 1024 */

    OCR0A = 78; /* 8MHz clock / 1024 (from TCCR0B flags) / 100 (for ~10ms delay) */
    OCR3A = 7812 / FPS; /* 8MHz clock / 1024 / FPS */

    /* Enable timer interrupts */
    TIMSK0 |= _BV(OCIE0A);
    TIMSK3 |= _BV(OCIE3A);

    /* Set seed for random numbers */
    srand(time(NULL));
}

void draw_crab(uint8_t pos, bool damaged)
{
    uint8_t left = pos * CRAB_WIDTH + 5;
    uint8_t bottom = SCREEN_HEIGHT - BOTTOM_GAP;

    rectangle left_bottom_leg;
    left_bottom_leg.left = left;
    left_bottom_leg.right = left + 10;
    left_bottom_leg.top = bottom - 5;
    left_bottom_leg.bottom = bottom;

    rectangle left_middle_leg;
    left_middle_leg.left = left;
    left_middle_leg.right = left + 10;
    left_middle_leg.top = bottom - 15;
    left_middle_leg.bottom = bottom - 10;

    rectangle left_top_leg;
    left_top_leg.left = left;
    left_top_leg.right = left + 10;
    left_top_leg.top = bottom - 25;
    left_top_leg.bottom = bottom - 20;

    rectangle body;
    body.left = left + 10;
    body.right = left + 40;
    body.top = bottom - 22;
    body.bottom = bottom - 3;

    rectangle left_pinser;
    left_pinser.left = left + 13;
    left_pinser.right = left + 18;
    left_pinser.top = bottom - CRAB_HEIGHT;
    left_pinser.bottom = bottom - 22;

    rectangle right_pinser;
    right_pinser.left = left + 32;
    right_pinser.right = left + 37;
    right_pinser.top = bottom - CRAB_HEIGHT;
    right_pinser.bottom = bottom - 22;

    rectangle left_eye;
    left_eye.left = left + 20;
    left_eye.right = left + 23;
    left_eye.top = bottom - 25;
    left_eye.bottom = bottom - 22;

    rectangle right_eye;
    right_eye.left = left + 27;
    right_eye.right = left + 30;
    right_eye.top = bottom - 25;
    right_eye.bottom = bottom - 22;

    rectangle left_iris;
    left_iris.left = left + 21;
    left_iris.right = left + 22;
    left_iris.top = bottom - 25;
    left_iris.bottom = bottom - 24;

    rectangle right_iris;
    right_iris.left = left + 28;
    right_iris.right = left + 29;
    right_iris.top = bottom - 25;
    right_iris.bottom = bottom - 24;

    rectangle right_bottom_leg;
    right_bottom_leg.left = left + 40;
    right_bottom_leg.right = left + 50;
    right_bottom_leg.top = bottom - 5;
    right_bottom_leg.bottom = bottom;

    rectangle right_middle_leg;
    right_middle_leg.left = left + 40;
    right_middle_leg.right = left + 50;
    right_middle_leg.top = bottom - 15;
    right_middle_leg.bottom = bottom - 10;

    rectangle right_top_leg;
    right_top_leg.left = left + 40;
    right_top_leg.right = left + 50;
    right_top_leg.top = bottom - 25;
    right_top_leg.bottom = bottom - 20;

    fill_rectangle(left_bottom_leg, (damaged == TRUE) ? DARK_RED : RED);
    fill_rectangle(left_middle_leg, (damaged == TRUE) ? DARK_RED : RED);
    fill_rectangle(left_top_leg, (damaged == TRUE) ? DARK_RED : RED);
    fill_rectangle(right_bottom_leg, (damaged == TRUE) ? DARK_RED : RED);
    fill_rectangle(right_middle_leg, (damaged == TRUE) ? DARK_RED : RED);
    fill_rectangle(right_top_leg, (damaged == TRUE) ? DARK_RED : RED);
    fill_rectangle(left_pinser, (damaged == TRUE) ? DARK_RED : RED);
    fill_rectangle(right_pinser, (damaged == TRUE) ? DARK_RED : RED);
    fill_rectangle(body, (damaged == TRUE) ? DARK_RED : RED);
    fill_rectangle(left_eye, WHITE);
    fill_rectangle(right_eye, WHITE);
    fill_rectangle(left_iris, BLUE);
    fill_rectangle(right_iris, BLUE);
}

void draw_turtle(uint8_t x, uint8_t y, bool lastRight)
{
    uint16_t left = x * CRAB_WIDTH + 15;

    rectangle left_bottom_leg;
    left_bottom_leg.left = left;
    left_bottom_leg.right = left + 5;
    left_bottom_leg.top = (lastRight == TRUE) ? y - 5 : y - 10;
    left_bottom_leg.bottom = (lastRight == TRUE) ? y + 5 : y;

    rectangle left_top_leg;
    left_top_leg.left = left;
    left_top_leg.right = left + 5;
    left_top_leg.top = (lastRight == TRUE) ? y - 40 : y - 45;
    left_top_leg.bottom = (lastRight == TRUE) ? y - 30 : y - 35;

    rectangle right_bottom_leg;
    right_bottom_leg.left = left + 30;
    right_bottom_leg.right = left + 35;
    right_bottom_leg.top = (lastRight == TRUE) ? y - 10 : y - 5;
    right_bottom_leg.bottom = (lastRight == TRUE) ? y : y + 5;

    rectangle right_top_leg;
    right_top_leg.left = left + 30;
    right_top_leg.right = left + 35;
    right_top_leg.top = (lastRight == TRUE) ? y - 45 : y - 40;
    right_top_leg.bottom = (lastRight == TRUE) ? y - 35 : y - 30;

    rectangle main_body;
    main_body.left = left + 10;
    main_body.right = left + 25;
    main_body.top = y - 40;
    main_body.bottom = y;

    rectangle left_body;
    left_body.left = left + 5;
    left_body.right = left + 10;
    left_body.top = y - 30;
    left_body.bottom = y - 10;

    rectangle right_body;
    right_body.left = left + 25;
    right_body.right = left + 30;
    right_body.top = y - 30;
    right_body.bottom = y - 10;

    rectangle head;
    head.left = left + 15;
    head.right = left + 20;
    head.top = y;
    head.bottom = y + 5;

    rectangle left_eye;
    left_eye.left = left + 16;
    left_eye.right = left + 17;
    left_eye.top = y + 4;
    left_eye.bottom = y + 5;

    rectangle right_eye;
    right_eye.left = left + 18;
    right_eye.right = left + 19;
    right_eye.top = y + 4;
    right_eye.bottom = y + 5;

    fill_rectangle(left_bottom_leg, GREEN);
    fill_rectangle(left_top_leg, GREEN);
    fill_rectangle(right_bottom_leg, GREEN);
    fill_rectangle(right_top_leg, GREEN);
    fill_rectangle(main_body, BROWN);
    fill_rectangle(left_body, BROWN);
    fill_rectangle(right_body, BROWN);
    fill_rectangle(head, GREEN);
    fill_rectangle(left_eye, CYAN);
    fill_rectangle(right_eye, CYAN);
}

void draw_bolt(uint8_t pos, uint8_t size)
{
    uint16_t left = pos * CRAB_WIDTH + (CRAB_WIDTH / 2) + 5;
    uint16_t bottom = SCREEN_HEIGHT - BOTTOM_GAP - (CRAB_HEIGHT / 2);

    for (uint8_t i = size; i > 0; i--)
    {
        rectangle vertical;
        vertical.left = left - (3 * i);
        vertical.right = left + (3 * i);
        vertical.top = bottom - (6 * i);
        vertical.bottom = bottom + (6 * i);

        rectangle horizontal;
        horizontal.left = left - (6 * i);
        horizontal.right = left + (6 * i);
        horizontal.top = bottom - (3 * i);
        horizontal.bottom = bottom + (3 * i);

        fill_rectangle(vertical, (i % 2 == 1) ? BEIGE : LIGHT_BROWN);
        fill_rectangle(horizontal, (i % 2 == 1) ? BEIGE : LIGHT_BROWN);
    }
}

void clear_crab()
{
    uint8_t left = position * CRAB_WIDTH + 5;
    uint8_t bottom = SCREEN_HEIGHT - BOTTOM_GAP;

    rectangle left_bottom_leg;
    left_bottom_leg.left = left;
    left_bottom_leg.right = left + 10;
    left_bottom_leg.top = bottom - 5;
    left_bottom_leg.bottom = bottom;

    rectangle left_middle_leg;
    left_middle_leg.left = left;
    left_middle_leg.right = left + 10;
    left_middle_leg.top = bottom - 15;
    left_middle_leg.bottom = bottom - 10;

    rectangle left_top_leg;
    left_top_leg.left = left;
    left_top_leg.right = left + 10;
    left_top_leg.top = bottom - 25;
    left_top_leg.bottom = bottom - 20;

    rectangle body;
    body.left = left + 10;
    body.right = left + 40;
    body.top = bottom - 22;
    body.bottom = bottom - 3;

    rectangle left_pinser;
    left_pinser.left = left + 13;
    left_pinser.right = left + 18;
    left_pinser.top = bottom - CRAB_HEIGHT;
    left_pinser.bottom = bottom - 22;

    rectangle right_pinser;
    right_pinser.left = left + 32;
    right_pinser.right = left + 37;
    right_pinser.top = bottom - CRAB_HEIGHT;
    right_pinser.bottom = bottom - 22;

    rectangle left_eye;
    left_eye.left = left + 20;
    left_eye.right = left + 23;
    left_eye.top = bottom - 25;
    left_eye.bottom = bottom - 22;

    rectangle right_eye;
    right_eye.left = left + 27;
    right_eye.right = left + 30;
    right_eye.top = bottom - 25;
    right_eye.bottom = bottom - 22;

    rectangle left_iris;
    left_iris.left = left + 21;
    left_iris.right = left + 22;
    left_iris.top = bottom - 25;
    left_iris.bottom = bottom - 24;

    rectangle right_iris;
    right_iris.left = left + 28;
    right_iris.right = left + 29;
    right_iris.top = bottom - 25;
    right_iris.bottom = bottom - 24;

    rectangle right_bottom_leg;
    right_bottom_leg.left = left + 40;
    right_bottom_leg.right = left + 50;
    right_bottom_leg.top = bottom - 5;
    right_bottom_leg.bottom = bottom;

    rectangle right_middle_leg;
    right_middle_leg.left = left + 40;
    right_middle_leg.right = left + 50;
    right_middle_leg.top = bottom - 15;
    right_middle_leg.bottom = bottom - 10;

    rectangle right_top_leg;
    right_top_leg.left = left + 40;
    right_top_leg.right = left + 50;
    right_top_leg.top = bottom - 25;
    right_top_leg.bottom = bottom - 20;

    fill_rectangle(left_bottom_leg, BLACK);
    fill_rectangle(left_middle_leg, BLACK);
    fill_rectangle(left_top_leg, BLACK);
    fill_rectangle(right_bottom_leg, BLACK);
    fill_rectangle(right_middle_leg, BLACK);
    fill_rectangle(right_top_leg, BLACK);
    fill_rectangle(left_pinser, BLACK);
    fill_rectangle(right_pinser, BLACK);
    fill_rectangle(body, BLACK);
    fill_rectangle(left_eye, BLACK);
    fill_rectangle(right_eye, BLACK);
    fill_rectangle(left_iris, BLACK);
    fill_rectangle(right_iris, BLACK);
}

void clear_turtle(uint8_t x, uint16_t y)
{
    rectangle lastPos;
    lastPos.left = x * CRAB_WIDTH + 15;
    lastPos.right = (x * CRAB_WIDTH + 15) + TURTLE_WIDTH;
    lastPos.top = y - TURTLE_HEIGHT;
    lastPos.bottom = y + 10;

    fill_rectangle(lastPos, BLACK);
}

void clear_bolt(uint8_t x)
{
    rectangle lastPos;
    lastPos.left = x * CRAB_WIDTH + 5;
    lastPos.right = (x * CRAB_WIDTH + 5) + CRAB_WIDTH;
    lastPos.top = SCREEN_HEIGHT - BOTTOM_GAP - CRAB_HEIGHT - 10;
    lastPos.bottom = SCREEN_HEIGHT;

    fill_rectangle(lastPos, BLACK);
}

ISR(TIMER3_COMPA_vect) {
}

ISR(TIMER0_COMPA_vect) {
    if (is_left_pressed() && position > 0 && finished == FALSE)
    {
        clear_crab();
        --position;
        draw_crab(position, damaged);
    }
    if (is_right_pressed() && position < 5 && finished == FALSE)
    {
        clear_crab();
        ++position;
        draw_crab(position, damaged);
    }
}

ISR(INT6_vect) 
{
    ++tick;

    if (tick >= 3 && finished == FALSE)
    {
        spawnTurtles();
        animateTurtles();
        spawnBolts();
        animateBolts();
        clear_crab(position);
        draw_crab(position, damaged);
        draw_info();

        tick = 0;
        ++tick3;
    }

    if (tick3 >= 10 && finished == FALSE)
    {
        damaged = FALSE;
        tick3 = 0;
    }
}

bool toggle(bool value)
{
    if (value == TRUE)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void remove_turtle(struct turtle *array, int index, int array_length)
{
   int i;
   for(i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}

void remove_bolt(struct bolt *array, int index, int array_length)
{
   int i;
   for(i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}

void animateTurtles(void)
{
    for (uint16_t i = 0; i < activeTurtles; i++)
    {        
        clear_turtle(turtles[i].x, turtles[i].y);

        if ((turtles[i].y >= SCREEN_HEIGHT - BOTTOM_GAP - CRAB_HEIGHT) && turtles[i].x == position)
        {
            remove_turtle(turtles, i, MAX_TURTLES);

            --activeTurtles;
            ++score;

            clear_crab();
            draw_crab(position, FALSE);
        }
        else if (turtles[i].y >= SCREEN_HEIGHT)
        {
            remove_turtle(turtles, i, MAX_TURTLES);
            --activeTurtles;
        }
        else
        {
            turtles[i].y = turtles[i].y + 1;
            turtles[i].lastRight = toggle(turtles[i].lastRight);

            draw_turtle(turtles[i].x, turtles[i].y, turtles[i].lastRight);
        }
    }
}

void animateBolts(void)
{
    for (uint16_t i = 0; i < activeBolts; i++)
    {
        if (++bolts[i].tick >= 50)
        {
            bolts[i].tick = 0;
            ++bolts[i].size;

            if (bolts[i].size >= 5)
            {
                clear_bolt(bolts[i].x);
                
                if (bolts[i].x == position)
                {
                    damaged = TRUE;
                    draw_crab(position, damaged);
                    --lives;
                }

                remove_bolt(bolts, i, MAX_BOLTS);
                --activeBolts;
            }
        }
        else
        {
            clear_bolt(bolts[i].x);
            draw_bolt(bolts[i].x, bolts[i].size);
        }
    }
}

void spawnTurtle(uint8_t x)
{
    if (activeTurtles <= MAX_TURTLES)
    {    
        turtles[activeTurtles].x = x;
        turtles[activeTurtles].y = 40;
        turtles[activeTurtles].lastRight = TRUE;

        ++activeTurtles;
    }
}

void spawnTurtles(void)
{
    if (rand() % 5000 <= difficulty)
    {
        spawnTurtle(rand() % 6);
    }
}

void spawnBolt(uint8_t x)
{
    if (activeBolts <= MAX_BOLTS)
    {
        bolts[activeBolts].x = x;
        bolts[activeBolts].size = 1;

        ++activeBolts;
    }
}

void spawnBolts(void)
{
    if (rand() % 10000 <= difficulty)
    {
        spawnBolt(rand() % 6);
    }
}

void draw_info(void) 
{
    char str[50];
    sprintf(str, "Score: %04d", score);
    display_string_xy(str, 0, 0);

    sprintf(str, "Lives: %01d", lives);
    display_string_xy(str, SCREEN_WIDTH - 50, 0);
}

void game_over(void)
{    
    display_string_xy("Game Over", SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2);
    
    char str[50];
    sprintf(str, "Score: %04d", score);
    display_string_xy(str, SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 10);

    finished = TRUE;
}

int main() 
{
    init();

    sei();

    draw_crab(position, FALSE);
    spawnTurtle(rand() % 6);

    for (;;) 
    {
        if (finished == FALSE)
        {
            if (lives <= 0)
            {
                game_over();
            }

            if (tick2++ >= 3)
            {
                ++timeElapsedSinceLevelUp;
                tick2 = 0;
            }
            
            if (timeElapsedSinceLevelUp >= DIFFICULTY_TIMER)
            {
                difficulty++;
                timeElapsedSinceLevelUp = 0;
            }
        }
    }
}