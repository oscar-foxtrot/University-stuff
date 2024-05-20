Sum MACRO X1, X2, X3, X4, X5, X6
	LOCAL S, cntr
.DATA 
	S DD (0)
	cntr DB (1)
.CODE 
	PUSH EBX
	INEAX MACRO B
		IF (type B) EQ 4
			MOV EAX, B
		ELSE
			MOVZX EAX, B
		ENDIF
	ENDM
	
	FOR P, <X1, X3, X5>
		IFNB <P>
			INEAX P
			ADD S, EAX
		ENDIF
	ENDM
	FOR P, <X2, X4, X6>
		INC cntr
		IFNB <P>
			MOVZX EBX, cntr
			INEAX P
			MUL EBX
			ADD S, EAX
		ENDIF
	ENDM
	
	MOV EAX, S
	POP EBX
ENDM
