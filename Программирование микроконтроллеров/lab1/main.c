/*
 * GccApplication1.c
 *
 * Created: 24.09.2025 13:58:12
 * Author : ivan
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "avr/iom2560.h"

#define BOOL uint8_t
#define TRUE 1
#define FALSE 0

#define DEBOUNCE_DELAY 50

void allLightsMode();
void ledRoadMode();
void everySecondMode();

typedef void (*ModeFunction)(void);

uint8_t powerButtonPrevState = FALSE;
uint8_t isPowerOn = FALSE;

uint8_t modeButtonPrevState = FALSE;

uint8_t speedButtonPrevState = FALSE;

ModeFunction modes[] = {
    ledRoadMode,
    everySecondMode,
    allLightsMode
};
uint8_t currentMode = 0;
uint8_t countModes = 3;

uint8_t readButton(uint8_t pin) {
    if ((PINA & (1 << pin)) == 0) {
        _delay_ms(DEBOUNCE_DELAY);
        if ((PINA & (1 << pin)) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

void updatePowerButton() {
    uint8_t currentState = readButton(0);
    
    if (currentState == TRUE && powerButtonPrevState == FALSE) {
        isPowerOn = !isPowerOn;
    }
    
    powerButtonPrevState = currentState;
}

void updateModeButton() {
    uint8_t currentState = readButton(1);
    
    if (currentState == TRUE && modeButtonPrevState == FALSE) {
        currentMode = (currentMode + 1) % countModes;
    }
    
    modeButtonPrevState = currentState;
}

// 3 скорости
uint8_t speed = 0;

void updateSpeedButton() {
	uint8_t currentState = readButton(2);
	
	if (currentState == TRUE && speedButtonPrevState == FALSE) {
		speed = (speed + 1) % 3;
	}
	
	speedButtonPrevState = currentState;
}

void updateButtons(){
	updatePowerButton();
	updateModeButton();
	updateSpeedButton();
}

void nonBlockingDelayWithCheck(uint16_t ms) {
	for (uint16_t i = 0; i < ms; i++) {
		_delay_ms(1);
		updateButtons();
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

int main(void) {
    DDRB = 0xFF;
    DDRA = 0x00;
    PORTA = 0b00000111;
    PORTB = 0;
    
    while (1) {       
        if (isPowerOn == TRUE) {
            modes[currentMode]();
        } else {
			updateButtons();
            PORTB = 0;
        }
    }
}