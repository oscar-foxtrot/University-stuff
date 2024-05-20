Volume MACRO p1,p2,p3,p4,p5,p6,p7
	PUSH EAX
	XOR EAX, EAX
	FOR p, <p1,p2,p3,p4,p5,p6,p7>
		IFNB <p>
			ADD EAX, (type p)
		ENDIF
	ENDM
	OUTU EAX
	POP EAX
ENDM