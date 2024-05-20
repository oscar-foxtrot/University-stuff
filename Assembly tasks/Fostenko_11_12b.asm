INCLUDE settings.inc
INCLUDE io2020.inc
M = .
N = .
.STACK 4096
.DATA
A DB M DUP (?)
B DB N DUP (?)
.CODE
	PRINT PROC ;Parameters are passed through stack
		PUSH EBP
		MOV EBP, ESP
		PUSH EAX
		PUSH EDX
		PUSH ECX
		XOR EDX, EDX
		MOV ECX, [EBP+12]
		MOV EAX, [EBP+8]
	printlp1: OUTI byte ptr [EAX][EDX]
		OUTCHAR ' '
		INC EDX
		CMP EDX, ECX
		JNE printlp1
		POP ECX
		POP EDX
		POP EAX
		POP EBP
		RET 8
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
	MOV EAX, N-1
	SHR EAX, 1
	MOV AL, B[EAX]
	CMP AL, A[M-1]
	JNE opt2
	PUSH M
	PUSH offset A
	CALL PRINT
	EXIT
opt2: PUSH N
	PUSH offset B
	CALL PRINT
	EXIT
END start