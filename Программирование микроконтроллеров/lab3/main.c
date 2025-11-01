/*
 * GccApplication1.c
 *
 * Created: 24.09.2025 13:58:12
 * Author : ivan
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "avr/iom2560.h"
#include <avr/interrupt.h>

#define BOOL uint8_t
#define TRUE 1
#define FALSE 0

void allLightsMode();
void ledRoadMode();
void everySecondMode();

typedef void (*ModeFunction)(void);

uint8_t isPowerOn = FALSE;

ModeFunction modes[] = {
    ledRoadMode,
    everySecondMode,
    allLightsMode
};
uint8_t currentMode = 0;
uint8_t countModes = 3;

// 3 скорости
uint8_t speed = 0;

void nonBlockingDelayWithCheck(uint16_t ms) {
	for (uint16_t i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

void makeDelay(){
	switch (speed){
		case 0:
		nonBlockingDelayWithCheck(200);
		break;
		case 1:
		nonBlockingDelayWithCheck(500);
		break;
		case 2:
		nonBlockingDelayWithCheck(1000);
		break;
	}
}

void everySecondMode() {
    PORTB = 0b10101010;
    makeDelay();
    PORTB = 0b01010101;
    makeDelay();
}

void ledRoadMode() {
    static uint8_t counter = 0;
    PORTB = (1 << counter);
    counter = (counter + 1) % 8;
    makeDelay();
}

void allLightsMode() {
    PORTB = 0xFF;
    makeDelay();
    PORTB = 0;
    makeDelay();
}

ISR(INT0_vect) { isPowerOn = !isPowerOn; }
ISR(INT1_vect) { currentMode = (currentMode + 1) % countModes; }
ISR(INT2_vect) { speed = (speed + 1) % 3; }

int main(void) {
	EICRA = (0b10 << ISC00) |
			(0b10 << ISC10) |
			(0b10 << ISC20);

	EIMSK = (1 << INT0) | 
			(1 << INT1) |
			(1 << INT2);
	
	sei();
	
    DDRB = 0xFF;
	DDRD = 0;
	PORTD = 0b00000111;
    PORTB = 0;
    
    while (1) {       
        if (isPowerOn == TRUE) {
            modes[currentMode]();
        } else {
            PORTB = 0;
        }
    }
}