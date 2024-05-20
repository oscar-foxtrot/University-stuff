INCLUDE settings.inc
INCLUDE io2020.inc
N=3
.CODE
start:
	MOV ECX, N-2
	ININT EBX
	ININT EDX
	SUB EBX, EDX
lp0: MOV EAX, EDX
	ININT EDX
	SUB EAX, EDX
	CMP EAX, EBX
	JNE fin2
	loop lp0
	OUTSTR <'Да'>
	EXIT
fin2: OUTSTR <'Нет'>
	EXIT
END start