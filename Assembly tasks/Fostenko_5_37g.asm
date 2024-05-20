INCLUDE settings.inc
INCLUDE io2020.inc
.CODE
start:
	N=
	MOV ECX, N-2
	ININT EDX ;EDX - for the 2nd small number
	ININT EAX ;EAX - for the 1st (the most) small number
	CMP EDX, EAX
	JGE inp0
	XCHG EDX, EAX
inp0: ININT EBX
	CMP EBX, EDX
	JGE lp0
	XCHG EBX, EDX
	CMP EDX, EAX
	JGE lp0
	XCHG EDX, EAX
lp0: loop inp0
	OUTI EAX
	OUTCHAR ' '
	OUTI EDX
	EXIT
END start