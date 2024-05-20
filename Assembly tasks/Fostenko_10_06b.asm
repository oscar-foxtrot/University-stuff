	
IF M EQ 1
	MOV ECX, 0
lp1: OUTI A[2*ECX]
	OUTCHAR ' '
	ADD ECX,1
	CMP ECX, N
	JNE lp1
ELSE
	XOR ECX, ECX
	LEA ESI, A
col2: MOV BX, [ESI] ;BX for the greatest value in the coloumn 
	PUSH ECX
	MOV ECX, N*(M-1)
col3: CMP [ESI][2*ECX], BX
	JNG skp2
	MOV BX, [ESI][2*ECX]
skp2: SUB ECX, N
	CMP ECX, 0
	JNE col3
	ADD ESI, 2
	POP ECX
	INC ECX
	OUTI BX
	OUTCHAR ' '
	CMP ECX, N
	JNE col2 
ENDIF