
.include "m2560def.inc"

; Определения типов
.equ TRUE = 1
.equ FALSE = 0

; Глобальные переменные
.def isPowerOn = r20
.def currentMode = r17
.def speed = r18
.def temp = r19

.cseg

reset:
    rjmp init

init:
    ; Инициализация портов
    ldi r16, 0xFF
    out DDRB, r16    ; PORTB как выход
    
    ldi r16, 0x00
    out DDRD, r16    ; PORTD как вход
	ldi r16, 0b00000111
	out PORTD, r16
    
    sei
    
    clr isPowerOn
    ldi currentMode, 0
    ldi speed, 0
    
    rjmp main_loop

power_off:
	clr r16
	out PORTB, r16
	rjmp main_loop

main_loop:
	rcall delay
    sbis PIND, 0     ; Если кнопка Power не нажата - пропускаем
    rcall check_power_button

	sbis PIND, 1     ; Если кнопка Mode не нажата - пропускаем
    rcall check_mode_button

	sbis PIND, 2     ; Если кнопка Speed не нажата - пропускаем
    rcall check_speed_button

	cpi isPowerOn, 0 ; Выключение гирлянды
	breq power_off

	rcall select_mode

	rjmp main_loop

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


check_power_button:
    wait_power_release:
        sbis PIND, 0    ; Ждем, пока кнопка будет отпущена
        rjmp wait_power_release
	com isPowerOn
    ret

check_mode_button:
    wait_mode_release:
        sbis PIND, 1
        rjmp wait_mode_release
        
    inc currentMode
    cpi currentMode, 3
    breq reset_mode
    rjmp end_mode_check
    
	reset_mode:
		clr r16
		out PORTB, r16
		ldi currentMode, 0
    
	end_mode_check:
		ret


check_speed_button:
    wait_speed_release:
        sbis PIND, 2    ; Ждем, пока кнопка будет отпущена
        rjmp wait_speed_release
    inc speed
    cpi speed, 3
    breq reset_speed
    rjmp end_speed_check
    
	reset_speed:
		ldi speed, 0
    
	end_speed_check:
		ret



mode_1:
	in r16, PORTB
	cpi r16, 0
	breq set_value
	rjmp end_check

	set_value:
	ldi r16, 0b00000001
	out PORTB, r16
	rjmp main_loop

	end_check:
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

delay:
	LDI R21,255
	sub r21, speed
	M3: LDI R22, 0
		M2: LDI R23,0
			M1: INC R23
			BRNE M1
		INC R22
		BRNE M2
	INC R21
	BRNE M3
	RET
