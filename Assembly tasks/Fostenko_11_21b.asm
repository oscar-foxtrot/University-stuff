INEAX PROC
	XOR EAX, EAX
	
	INHEX PROC
		PUSH EDX
		
		INCHAR DL
		CMP DL, ' '
		JE fin
		CMP DL, '0'
		JB jletter
		CMP DL, '9'
		JA jletter
		SUB DL, '0'
		JMP nxt
	jletter: SUB DL, 'A'
		ADD DL, 10
		
	nxt: MOVZX EDX, DL
		SHL EAX, 4
		OR EAX, EDX
		CALL INHEX	; <- RECURSION here
		
	fin: POP EDX
		RET
	INHEX ENDP
	
	CALL INHEX
	RET
INEAX ENDP

