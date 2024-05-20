INCLUDE settings.inc
INCLUDE io2020.inc
.CODE
start:
	MOV EBX, 10
	XOR EAX, EAX
	XOR ECX, ECX
	MOV ESI, 1
	INCHAR CL
	CMP CL, '-'
	JNE cnt2
	MOV ESI, -1
	INCHAR CL
	JMP cnt3
cnt2: CMP CL, '+'
	JNE cnt3
	INCHAR CL
cnt3: CMP CL, ' '
	JE ert1
rpt: CMP CL, '0'
	JB ert
	CMP CL, '9'
	JA ert
	SUB ECX, '0'
	MUL EBX
	JO ert2
	ADD EAX, ECX
	JO ert2
	INCHAR CL
	JMP rpt
	
ert: CMP CL, ' '
	JNE ert1
	IMUL ESI
	OUTI EAX
	EXIT
ert2: INCHAR CL
	CMP CL, ' '
	JNE ert2s
	CMP EAX, 80000000h
	JNE ert2s
	CMP ESI, -1
	JNE ert2s
	JMP ert
ert2s: CMP CL, ' '
	JE ert2a
	CMP CL, '0'
	JB ert1
	CMP CL, '9'
	JA ert1
	INCHAR CL
	JMP ert2s
ert2a: OUTSTR <'Переполнение'>
	EXIT
ert1: OUTSTR <'Ошибка'>
	EXIT
end start