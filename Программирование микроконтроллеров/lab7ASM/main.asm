.include "m2560def.inc"
.cseg
.org 0
    rjmp reset
.org INT0addr          ; Вектор прерывания INT0
    rjmp INT0_vect
.org INT1addr          ; Вектор прерывания INT1  
    rjmp INT1_vect
.org INT2addr          ; Вектор прерывания INT2
	rjmp INT2_vect
.org OC0Aaddr    ; Таймер 0 Compare A
    rjmp timer_interrupt

.def isPowerOn = r20
.def currentMode = r17
.def speed = r18
.def temp = r19


reset:
    ldi r16, high(RAMEND)
    out SPH, r16
    ldi r16, low(RAMEND)
    out SPL, r16

    ldi r16, 0xFF
    out DDRB, r16    ; PORTB  
    
    ldi r16, 0x00
    out DDRD, r16    ; PORTD  
	ldi r16, 0b00000111
	out PORTD, r16

    ; Настройка Timer0 (8-битный)
    ldi r16, (1 << WGM01)  ; CTC режим
    out TCCR0A, r16
    
    ldi r16, (1 << CS02) | (1 << CS00)  ; Предделитель 1024
    out TCCR0B, r16
    
	ldi r16, 243
	out OCR0A, r16

    ldi r16, (1 << OCIE0A) ; Разрешить прерывание
    sts TIMSK0, r16

	; Инициализация EICRA (прерывания по спадающему фронту)
	ldi r16, (0b10 << ISC00) | (0b10 << ISC10) | (0b10 << ISC20)
	sts EICRA, r16

	; Разрешение прерываний
	ldi r16, (1 << INT0) | (1 << INT1) | (1 << INT2)
	out EIMSK, r16

	clr isPowerOn
	clr speed

    sei

main_loop:
    rjmp main_loop

timer_interrupt:
    push r16
    in r16, SREG
    push r16
    
	cpi isPowerOn, 0
	breq end_of_timer_int

	rcall select_mode

	end_of_timer_int:
    pop r16
    out SREG, r16
    pop r16
    reti

select_mode:
	cpi currentMode, 0
	breq call_mode_1

	cpi currentMode, 1
	breq call_mode_2

	cpi currentMode, 2
	breq call_mode_3

	rjmp end_mode_selecting

	call_mode_1:
		rcall mode_1
		rjmp end_mode_selecting
	call_mode_2:
		rcall mode_2
		rjmp end_mode_selecting
	call_mode_3:
		rcall mode_3
		rjmp end_mode_selecting

	end_mode_selecting:
	ret

mode_1:
	in r16, PORTB
	cpi r16, 0
	breq set_value
	rjmp end_check_mode_1

	set_value:
	ldi r16, 0b00000001
	out PORTB, r16
	ret

	end_check_mode_1:
	lsl r16
	out PORTB, r16
	ret

mode_2:
	in r16, PORTB
	cpi r16, 0b01010101
	breq invert_mode_2

	ldi r16, 0b01010101
	out PORTB, r16
	rjmp end_check_mode_2

	invert_mode_2:
	in r16, PORTB
	com r16
	out PORTB, r16

	end_check_mode_2:
	ret

mode_3:
	in r16, PORTB
	cpi r16, 0
	breq invert_mode_3

	ldi r16, 0
	out PORTB, r16
	rjmp end_check_mode_3

	invert_mode_3:
	in r16, PORTB
	com r16
	out PORTB, r16

	end_check_mode_3:
	ret

; Обработчик INT0 - переключение питания
INT0_vect:
    push r16
    in r16, SREG
    push r16
    
    com isPowerOn
	clr r16
	out PORTB, r16

    pop r16
    out SREG, r16
    pop r16
    reti

; Обработчик INT1 - смена режима
INT1_vect:
    push r16
    in r16, SREG
    push r16
    
    inc currentMode    ; currentMode + 1
    cpi currentMode, 3  ; MODE_COUNT = 3
    brlo int1_end
    ldi currentMode, 0           ; Обнулить если достигли максимума
    
int1_end:
    pop r16
    out SREG, r16
    pop r16
    reti

; Обработчик INT2 - смена скорости
INT2_vect:
    push r16
    in r16, SREG
    push r16

	inc speed
    cpi speed, 3
    brlo set_speed    ; Если speed < 3, переходим к установке
    ldi speed, 0      ; Иначе сбрасываем в 0

	set_speed:
	cpi speed, 0
	breq set_speed_0

	cpi speed, 1
	breq set_speed_1

	cpi speed, 2
	breq set_speed_2

	rjmp int2_end

	set_speed_0:
	ldi r16, 243
	out OCR0A, r16
	rjmp int2_end

	set_speed_1:
	ldi r16, 150
	out OCR0A, r16
	rjmp int2_end

	set_speed_2:
	ldi r16, 50
	out OCR0A, r16

	int2_end:
    pop r16
    out SREG, r16
    pop r16
    reti