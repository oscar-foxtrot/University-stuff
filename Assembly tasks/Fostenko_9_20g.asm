	MOV AX, D2
	MOV BX, AX
	AND BX, mask m2
	SHR BX, m2
	MOV D1, BX
	MOV BX, AX
	AND BX, mask d2
	SHR BX, (d2-d1)
	OR D1, BX
	AND AX, mask y2
	SHL AX, y1
	OR D1, AX