Sum MACRO X1, X2, X3, X4, X5, X6
	LOCAL S
.DATA 
	S DD (0)
.CODE 
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
	MOV EBX, 1
	FOR P, <X2, X4, X6>
		INC EBX
		IFNB <P>
			INEAX P
			MUL EBX
			ADD S, EAX
		ENDIF
	ENDM
	MOV EAX, S
ENDM

