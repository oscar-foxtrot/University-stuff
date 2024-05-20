INCLUDE settings.inc
INCLUDE io2020.inc
M = .
N = .
.STACK 4096
.DATA
A DB M DUP (?)
B DB N DUP (?)
.CODE
	PRINT PROC ;Parameters are passed through registers. 
		PUSH EDX
		XOR EDX, EDX
	printlp1: OUTI byte ptr [ESI][EDX]
		OUTCHAR ' '
		INC EDX
		CMP EDX, ECX
		JNE printlp1
		POP EDX
		RET
	PRINT ENDP
	
start:
	XOR ECX, ECX
lp1: ININT A[ECX]
	INC ECX
	CMP ECX, M
	JNE lp1
	XOR ECX, ECX
lp2: ININT B[ECX]
	INC ECX
	CMP ECX, N
	JNE lp2
	MOV AX, N-1
	MOV CL, 2
	DIV CL
	MOVZX EAX, AL
	MOV AL, B[EAX]
	CMP AL, A[M-1]
	JNE opt2
	MOV ECX, M
	LEA ESI, A
	CALL PRINT
	EXIT
opt2: MOV ECX, N
	LEA ESI, B
	CALL PRINT
	EXIT
END start