
 /*
 * delay_as.s
 *
 * Author:	Tom Leonardsson & Carl Zetterberg
 *
 * Date:	2016-12-06
 *
 *
 * Filen innehåller ett antal olika långa delay subrutiner och gör dem globala så att C-kompilatorn kommer åt dem.
 */ 
 .global delay_1_micros 
 .global delay_micros
 .global delay_1_s
 .global delay_ps
 .global delay_s
 .global delay_ms
;==============================================================================
; Delay of 1 µs (including RCALL)
;==============================================================================
delay_1_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	NOP ; wait one cycle which is ~1 µs
	NOP
	NOP
	NOP
	NOP
	RET

;==============================================================================
; Delay of X µs
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */ 
	NOP ; wait one cycle which is ~1 µs
	NOP
	NOP
	NOP
	NOP
	NOP ; wait one cycle which is ~1 µs
	NOP
	NOP
	NOP
	NOP
	NOP
	
	DEC R24 ; Det är dåligt att sätta negativa tal, för storatal 
	CPI R24, 0			; if parameter is zero the loop is done
	BRNE delay_micros	;	restart function
	RET

delay_1_s:
	CALL delay_s
	RET

delay_ps:
	LDI R24, 250

	CALL delay_ms
	CALL delay_ms
	CALL delay_ms
	CALL delay_ms
	CALL delay_ms
	CALL delay_ms
	CALL delay_ms
	CALL delay_ms
	CALL delay_ms
	CALL delay_ms

	DEC R24
	CPI R24, 0
	BRNE delay_s
	RET

delay_s:
	LDI R24, 255
	CALL delay_ms
	CALL delay_ms
	CALL delay_ms		
	CALL delay_ms
	CALL delay_ms
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_ms:
	MOV R18, R24 ; copy R24 into R18, R18 is used for loop
loop_dms:
	LDI R24, 250 ; set R24 to 250
	RCALL delay_micros ; run delay_micros with parameter R24
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	DEC R18 ; decrese R18 
	CPI R18, 0			; check if R18 is down to zero
	BRNE loop_dms		;	continue!
	RET
 

