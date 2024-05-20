INCLUDE settings.inc
INCLUDE io2020.inc
.CODE
start:
	XOR ECX, ECX
rpt0: INCHAR AL
	CMP AL, ','
	JNE lp0
	CMP AH, 'Z'
	JNE rpt0
	INC ECX
	JMP rpt0
lp0: CMP AL, '.'
	JE nx1
	MOV AH, AL
	JMP rpt0
nx1: CMP AH, 'Z'
	JNE fin
	INC ECX
fin: OUTU ECX
	EXIT
END start