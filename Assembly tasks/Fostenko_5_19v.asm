INCLUDE settings.inc
INCLUDE io2020.inc
.CODE
start:
	ININT EAX
	XOR CL, CL
rpt: XOR EDX, EDX
	MOV EBX, 10
	DIV EBX
	CMP EDX, 0
	JNE n1
	INC CL
n1: CMP EAX, 0
	JNE rpt
fin: OUTU CL
	EXIT
end start