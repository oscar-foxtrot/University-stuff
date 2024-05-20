	MOV EDI, offset S[N-1]
	MOV AL, 'n'
	MOV ECX, N
	STD
	REPNE SCASB
	JNE nxt
	MOV byte ptr [EDI+1], 'N'

nxt: XOR ECX, ECX
rpt2: MOV BL, S[ECX]
	OUTCHAR BL
	INC ECX
	CMP ECX, N
	JNE rpt2