INCLUDE settings.inc
INCLUDE io2020.inc
.DATA
X DB 10 DUP (0)
.CODE
start: ;Note: It is obviously more rational to make use of RECORDS instead of ARRAYS
	MOV ECX, 9+'0'
rpt0: MOV X[ECX-'0'], CL
	CMP ECX, '0'
	DEC ECX
	JA rpt0
	XOR EAX, EAX
inp0: INCHAR AL
	CMP AL, '.'
	JE nxt0
	CMP AL, '0'
	JB inp0
	CMP AL, '9'
	JA inp0
	SUB AL, '0'
	MOV X[EAX], 0FFh
	JMP inp0
nxt0: MOV ECX, '0'
lp1: CMP X[ECX-'0'], 0FFh
	JNE lp1n
	OUTCHAR CL
	OUTCHAR ' '
lp1n: INC ECX
	CMP ECX, '9'+1
	JNE lp1
	EXIT
end start