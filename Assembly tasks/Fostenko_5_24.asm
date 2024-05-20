INCLUDE settings.inc
INCLUDE io2020.inc
.CODE
start:
	ININT EDI
	XOR EBX, EBX
	MOV ECX, EDI
lp2s: MOV EAX, EDI
	XOR EDX, EDX
	DIV ECX
	CMP EDX, 0
	JNZ lp2f
	INC EBX
lp2f: loop lp2s
	OUTU EBX
	EXIT
end start