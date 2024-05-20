INCLUDE settings.inc
INCLUDE io2020.inc
.CODE
start:
	;*note: The program doesn't work with memory - throws an error
	N=.
	Time Record h:4, m:6, s:6 ;type Time = 2, therefore we use WORD-long registers
	T Time N dup(<>)
	XOR ECX, ECX
	XOR EDX, EDX
lp0: ININT BX
	CMP BX, 7
	JAE nxt0
	INC EDX
nxt0: ININT BX
	ININT BX
	INC ECX
	CMP ECX, N
	JNE lp0
	OUTU EDX
	EXIT
END start