	MOV ECX, N
	CMP ECX, 3
	MOV AL, '*'	;Doesn't change flags
	STD 		;Changes DF to '1'
	JBE option1
	MOV ECX, N-3
	MOV ESI, offset S+(N-4)
	MOV EDI, offset S+(N-1) 
	REP MOVSB
	MOV ECX, 3
	JMP rpt1
option1: MOV EDI, offset S+N-1
rpt1: REP STOSB
