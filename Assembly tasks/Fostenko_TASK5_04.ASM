INCLUDE settings.inc
INCLUDE io2020.inc
.CODE
start:
	ININT ECX
	ININT EAX
	DEC ECX
	JZ fin01
	MOV EBX, EAX
lp0: ININT EDX
	CMP EBX, EDX
	JLE nxt0
	MOV EBX, EDX
nxt0: loop lp0
	CMP EBX, 0
	JZ finerr
	CDQ
	IDIV EBX
	OUTI EDX ;A remainder can only be a positive number (or ZERO)
	EXIT
finerr: OUTSTR <'Error'>
	EXIT
fin01: CMP EAX, 0
	JZ finerr
fin02: OUTCHAR '0'
	EXIT
END start