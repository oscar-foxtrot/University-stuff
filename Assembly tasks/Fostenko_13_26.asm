Prdw MACRO p1, p2, p3, p4, p5, p6, p7
	FOR p, <p1, p2, p3, p4, p5, p6, p7>
		IFNB <p>
			IF (type p) EQ 4
				OUTI p
				OUTCHAR ' '
			ENDIF
		ENDIF
	ENDM
ENDM