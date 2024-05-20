INCLUDE settings.inc
INCLUDE io2020.inc
.STACK 4096
.CODE
start:
	MOV EBP, ESP
	XOR AX, AX
	INCHAR AL
	CMP AX, '0'
	JB exc1
	CMP AX, '9'
	JA exc1
	MOV CX, AX
	JMP fin
	
rpt: XOR AX, AX
	INCHAR AL
exc1: CMP AL, '('
	JE rpt
	CMP AL, ','
	JE rpt
	CMP AL, ')'
	JE closepar
	PUSH AX
	JMP rpt
closepar: 
	POP BX
	POP CX
	POP DX
	CMP DL, 'm'
	JE min
	CMP CL, BL
	JB below1
	JMP frpt
below1:
	MOV CL, BL
	JMP frpt
min:
	CMP CL, BL
	JA above2
	JMP frpt
above2: MOV CL, BL
frpt: CMP ESP, EBP
	JE fin
	PUSH CX
	JMP rpt
fin: OUTCHAR CL
EXIT
end start