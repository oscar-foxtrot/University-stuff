INCLUDE settings.inc
INCLUDE io2020.inc
.CODE
start:
	;note*
	N=…
	Time record h:4, m:6, s:6
	MOV ECX, N-1
	XOR DI, DI ;DI for the greatest "m" value
	XOR SI, SI ;SI for the result
	ININT SI
	SHL SI, h
	ININT AX
	MOV DI, AX
	SHL AX, m
	OR SI, AX
	ININT AX
	OR SI, AX
lp1: ININT AX
	ININT BX
	ININT DX
	CMP BX, DI
	JBE lp2
	MOV DI, BX
	SHL BX, m
	SHL AX, h
	XOR SI, SI
	MOV SI, DX
	OR SI, BX
	OR SI, AX
lp2: loop lp1
	
	MOV AX, SI
	AND AX, mask h
	SHR AX, h
	OUTU AX
	OUTCHAR ' '
	MOV AX, SI
	AND AX, mask m
	SHR AX, m
	OUTU AX
	OUTCHAR ' '
	AND SI, mask s
	OUTU SI
	
	EXIT
end start