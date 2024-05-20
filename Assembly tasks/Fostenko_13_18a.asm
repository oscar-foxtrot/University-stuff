Zero MACRO X, T
	IFIDNI <T>, <First>		;CASE-INSENSITIVE
		IF (type X) EQ qword
			MOV dword ptr X, 0
			MOV dword ptr X+4, 0
		ELSE
			MOV X, 0
		ENDIF
	ELSEIFIDNI <T>, <Last> 	;CASE-INSENSITIVE
		IF (type X) EQ qword
			MOV dword ptr X[(size X)-8], 0
			MOV dword ptr X[(size X)-4], 0
		ELSE
			MOV X[(size X)-(type X)], 0
		ENDIF
	ENDIF
ENDM