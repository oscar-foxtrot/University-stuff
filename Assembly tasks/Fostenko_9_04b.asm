INCLUDE settings.inc
INCLUDE io2020.inc
N=.
Time Record h:4, m:6, s:6 ;type Time = 2, therefore we use WORD-long registers
.DATA
T Time N dup(<>)
.CODE
start:
	XOR ECX, ECX
	XOR EDX, EDX
lp0: ININT BX
	CMP BX, 7
	JAE nxt0
	INC EDX
nxt0: SHL BX, h
	MOV T[ECX], BX
	ININT BX
	SHL BX, m
	OR T[ECX], BX
	ININT BX
	OR T[ECX], BX
	ADD ECX, 2 ; type Time = 2
	CMP ECX, 2*N
	JNE lp0
	OUTU EDX
	EXIT
END start