/*
 * GccApplication1.c
 *
 * Created: 24.09.2025 13:58:12
 * Author : ivan
 */ 
#include <avr/io.h>
#include "avr/iom2560.h"
#include <avr/interrupt.h>

#define BOOL uint8_t
#define TRUE 1
#define FALSE 0

uint8_t isPowerOn = FALSE;

uint8_t currentMode = 0;
uint8_t countModes = 3;

// 3 скорости
uint8_t speed = 0;
const uint16_t mode_speeds[3] = {
	244,
	488,
	976
};

void timer1_init(void) {
	TCCR1B = 0x00;
	TCNT1 = 0x0000;
	OCR1A = mode_speeds[speed];
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
}

ISR(INT0_vect) { isPowerOn = !isPowerOn; }
ISR(INT1_vect) { currentMode = (currentMode + 1) % countModes; }
ISR(INT2_vect) { 
	speed = (speed + 1) % 3; 
	OCR1A = mode_speeds[speed];
	TCNT1 = 0x0000;
}

static uint8_t counter = 0;
ISR(TIMER1_COMPA_vect) {
	if(isPowerOn == FALSE){
		PORTB = 0;
		return;
	}
	switch (currentMode){
		case 0:
			if(PORTB == 0) PORTB = 0xFF;
			else PORTB = 0;
			break;
		case 1:
			if(PORTB == 0b01010101) PORTB ^= 0xFF;
			else PORTB = 0b01010101;
			break;
		case 2:
			counter = (counter + 1) % 8;
			PORTB = (1 << counter);
			break;
	}
}


int main(void) {
	EICRA = (0b10 << ISC00) |
			(0b10 << ISC10) |
			(0b10 << ISC20);

	EIMSK = (1 << INT0) | 
			(1 << INT1) |
			(1 << INT2);
	
	timer1_init();
	sei();
	
    DDRB = 0xFF;
	DDRD = 0;
	PORTD = 0b00000111;
    PORTB = 0;
    
    while (1) {     
    }
}