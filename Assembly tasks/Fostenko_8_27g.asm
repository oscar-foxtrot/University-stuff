.DATA
	K DB ?
.CODE
	ININT K
	CMP K, 0
	JE finerr0
	CMP K, 16
	JA finerr0
	MOV EAX, 11b
	MOV CL, 16
	SUB CL, K
	SHL CL, 1
	SHL EAX, CL
	AND EAX, PX
	SHR EAX, CL
	OUTU EAX
	CLC
	JMP fin0
finerr0: STC
fin0:
	
	