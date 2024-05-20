INCLUDE settings.inc
INCLUDE io2020.inc
N=4
.DATA
X DW N DUP (?)
.CODE
start:
	MOV ECX, N
inp0: ININT word ptr X[ECX*2-2]
	loop inp0
	MOV DX, X[2*(N-1)]
	MOV BX, X[2*(N-2)]
	MOV ECX, N-2
	XOR EDI, EDI ; The result will be here
lp0: MOV AX, X[2*ECX-2]
	CMP DX, AX
	JNE jlp0
	INC EDI
jlp0: MOV DX, BX
	MOV BX, AX
	loop lp0
	OUTU EDI
	EXIT
END start