Sum MACRO p1, p2, p3, p4, p5, p6, p7
	LOCAL p
.DATA
	p db (0)
.CODE 
	FOR a, <p1, p2, p3, p4, p5, p6, p7>
		IFNB <a>
			ADD p, type a
		ENDIF
	ENDM
		OUTU p
ENDM