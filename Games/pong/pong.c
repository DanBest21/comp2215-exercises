/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcd/lcd.h"
#include "rotary.h"
#include "led.h"


#define BALL_SIZE	4
#define BAT_WIDTH	50
#define BAT_HEIGHT	2
#define BAT_INC		10


const rectangle start_bat = {(LCDWIDTH-BAT_WIDTH)/2, (LCDWIDTH+BAT_WIDTH)/2, LCDHEIGHT-BAT_HEIGHT-1, LCDHEIGHT-1};
const rectangle start_ball = {(LCDWIDTH-BALL_SIZE)/2, (LCDWIDTH+BALL_SIZE)/2, 0, BALL_SIZE-1};

volatile rectangle bat, ball, last_bat, last_ball;
volatile uint16_t score;
volatile uint8_t lives;
volatile uint8_t fps = 0;

ISR(INT6_vect)
{
	fill_rectangle(last_ball, display.background);
	fill_rectangle(ball, RED);
	fill_rectangle(last_bat, display.background);
	fill_rectangle(bat, GREEN);
	last_ball = ball;
	last_bat = bat;
	char buffer[4];
	sprintf(buffer, "%03d", score);
	display_string_xy(buffer, 200, 20);
	fps++;
}

ISR(TIMER1_COMPA_vect)
{
	static int8_t xinc = 1, yinc = 1;
	ball.left   += xinc;
	ball.right  += xinc;
	ball.top    += yinc;
	ball.bottom += yinc;
	if (ball.right >= display.width-1 || ball.left <= 0)
		xinc = -xinc;
	if (ball.top <= 0)
		yinc = -yinc;
	if (ball.bottom == display.height-1 && ball.left <= bat.right && ball.right >= bat.left) {
		yinc = -yinc;
		if (!(++score % 10))
			OCR1A >>= 1;
	}
	if (rotary<0 && bat.left >= BAT_INC) {
		bat.left  -= BAT_INC;
		bat.right -= BAT_INC;
	}
	if (rotary>0 && bat.right < display.width-BAT_INC) {
		bat.left  += BAT_INC;
		bat.right += BAT_INC;
	}
	rotary = 0;
	if (ball.bottom > display.height) {
		lives--;
		led_brightness(0x03 << (lives << 1));
		ball = start_ball;
		bat = start_bat;
	}
}

ISR(TIMER3_COMPA_vect)
{
	char buffer[4];
	sprintf(buffer, "%03d", fps);
	display_string_xy(buffer, 40, 20);
	fps = 0;
}

int main()
{
	/* Clear DIV8 to get 8MHz clock */
	CLKPR = (1 << CLKPCE);
	CLKPR = 0;
	init_rotary();
	init_led();
	init_lcd();
	set_frame_rate_hz(61); /* > 60 Hz  (KPZ 30.01.2015) */
	/* Enable tearing interrupt to get flicker free display */
	EIMSK |= _BV(INT6);
	/* Enable rotary interrupt to respond to input */
	EIMSK |= _BV(INT4) | _BV(INT5);
	/* Enable game timer interrupt (Timer 1 CTC Mode 4) */
	TCCR1A = 0;
	TCCR1B = _BV(WGM12);
	TCCR1B |= _BV(CS10);
	TIMSK1 |= _BV(OCIE1A);
	/* Enable performance counter (Timer 3 CTC Mode 4) */
	TCCR3A = 0;
	TCCR3B = _BV(WGM32);
	TCCR3B |= _BV(CS32);
	TIMSK3 |= _BV(OCIE3A);
	OCR3A = 31250;
	/* Play the game */
	do {
		last_bat = bat = start_bat;
		last_ball = ball = start_ball;
		lives = 3;
		score = 0;
		OCR1A = 65535;
		led_on();
		sei();
		while(lives);
		cli();
		led_off();
		display_string_xy("Game Over", 90, 150);
		PORTB |= _BV(PB6);
		while(PINE & _BV(SWC))
		{
			if (PINB & _BV(PB6))
				led_on();
			else
				led_off();
		}
		clear_screen();
	} while(1);
}
