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

// 3 ��������
uint8_t speed = 0;
const uint16_t mode_speeds[3] = {
    244,
    488,
    976
};

// ==================== USART ������� ====================

// ������������� USART ��� ATmega2560
void USART_Init(void) {
    // ��������� �������� 9600 ��� ��� 1 ���
    UBRR0H = 0;
    UBRR0L = 12;  // ��� 1 ��� � 9600 ���
    
    // �������� ��������, ���������� � ���������� �� ������
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    
    // ������ �����: 8 ��� ������, 1 ����-���
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// �������� ������ �������
void USART_SendChar(char data) {
    // ���� ���� ����� �������� �����������
    while (!(UCSR0A & (1 << UDRE0)));
    // ���������� ������
    UDR0 = data;
}

// �������� ������
void USART_SendString(char *str) {
    while (*str) {
        USART_SendChar(*str);
        str++;
    }
}

// �������� ����� (��� �������)
void USART_SendNumber(uint8_t num) {
    USART_SendChar('0' + num);
}

// ���������� ���������� USART (����� ������ � ���������)
ISR(USART0_RX_vect) {
    char command = UDR0;  // ������ ���������� ������
    
    switch(command) {
        case '0':  // ���������
            isPowerOn = FALSE;
            USART_SendString("Power: OFF\r\n");
            break;
            
        case '1':  // ��������
            isPowerOn = TRUE;
            USART_SendString("Power: ON\r\n");
            break;
            
        case 'm':  // ��������� �����
        case 'M':
            currentMode = (currentMode + 1) % countModes;
            USART_SendString("Mode: ");
            USART_SendNumber(currentMode);
            USART_SendString("\r\n");
            break;
            
        case 's':  // ��������� ��������
        case 'S':
            speed = (speed + 1) % 3;
            OCR1A = mode_speeds[speed];
            TCNT1 = 0x0000;
            USART_SendString("Speed: ");
            USART_SendNumber(speed);
            USART_SendString("\r\n");
            break;
            
        case 'h':  // �������
        case 'H':
        case '?':
            USART_SendString("=== Commands ===\r\n");
            USART_SendString("0 - Power OFF\r\n");
            USART_SendString("1 - Power ON\r\n");
            USART_SendString("m - Next mode\r\n");
            USART_SendString("s - Next speed\r\n");
            USART_SendString("h - Help\r\n");
            break;
            
        default:
            USART_SendString("Unknown command. Press 'h' for help\r\n");
    }
}

// ==================== ������ � ���������� ====================

void timer1_init(void) {
    TCCR1B = 0x00;
    TCNT1 = 0x0000;
    OCR1A = mode_speeds[speed];
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
}

ISR(INT0_vect) { 
    isPowerOn = !isPowerOn; 
    USART_SendString("Button: Power ");
    USART_SendString(isPowerOn ? "ON\r\n" : "OFF\r\n");
}

ISR(INT1_vect) { 
    currentMode = (currentMode + 1) % countModes; 
    USART_SendString("Button: Mode ");
    USART_SendNumber(currentMode);
    USART_SendString("\r\n");
}

ISR(INT2_vect) { 
    speed = (speed + 1) % 3; 
    OCR1A = mode_speeds[speed];
    TCNT1 = 0x0000;
    USART_SendString("Button: Speed ");
    USART_SendNumber(speed);
    USART_SendString("\r\n");
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

// ==================== �������� ��������� ====================

int main(void) {
    // ��������� ������� ����������
    EICRA = (0b10 << ISC00) |
            (0b10 << ISC10) |
            (0b10 << ISC20);

    EIMSK = (1 << INT0) | 
            (1 << INT1) |
            (1 << INT2);
    
    // ������������� USART �� ��������� ����������
    USART_Init();
    
    // ������������� �������
    timer1_init();
    
    // ��������� ������
    DDRB = 0xFF;
    DDRD = 0;
    PORTD = 0b00000111;
    PORTB = 0;
    
    // �������������� ���������
    USART_SendString("=== Garland Controller ===\r\n");
    USART_SendString("ATmega2560 Ready!\r\n");
    USART_SendString("Press 'h' for commands list\r\n");
    
    // �������� ��� ����������
    sei();
    
    while (1) {     
        // �������� ���� ������ - ��� ������ � �����������
    }
}