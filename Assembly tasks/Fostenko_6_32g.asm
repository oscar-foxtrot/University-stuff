TA EQU <type A>
MOV EBX, TA*N
MOV ECX, TA
lp0: XOR EDI, EDI ; *N
	XOR EDX, EDX
lp1: MOV EAX, A[EBX][EDX]
	CMP EAX, A[EDI][ECX]
	JNE fin0
	ADD EDI, TA*N
	ADD EDX, TA
	CMP EDX, ECX
	JNE lp1
	ADD ECX, TA
	ADD EBX, TA*N
	CMP ECX, TA*N
	JNE lp0
	OUTSTR <'Yes'>
	JMP fin1
fin0: OUTSTR <'No'>
fin1: