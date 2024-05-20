INCLUDE settings.inc
INCLUDE io2020.inc
.CODE
start:
	XOR EAX, EAX   ;EAX is the "array"
	inp: INCHAR CL
		CMP CL, '.'
		JZ fin
		MOV EBX, 1
		SUB CL, 'a'
		SHL EBX, CL
		TEST EBX, EAX
		JNZ inp
		OR EAX, EBX
		ADD CL, 'a'
		OUTCHAR CL
	JMP inp	
	fin: EXIT
END start
