INCLUDE settings.inc
INCLUDE io2020.inc
.STACK 4096
.CODE
start:
	MOV EBP, ESP
	INCHAR AL
	CMP AL, '0'
	JB exc1
	CMP AL, '9'
	JA exc1
	MOV CL, AL
	JMP fin
	
rpt: INCHAR AL
exc1: CMP AL, '('
	JE rpt
	CMP AL, ','
	JE rpt
	CMP AL, ')'
	JE closepar
	DEC ESP
	MOV [ESP], byte ptr AL
	JMP rpt
closepar: 
	MOV byte ptr BL, [ESP]
	INC ESP
	MOV byte ptr CL, [ESP]
	INC ESP
	MOV byte ptr DL, [ESP]
	INC ESP
	CMP DL, 'm'
	JE min
	CMP CL, BL
	JB below1
	JMP frpt
below1:
	MOV CL, BL
	JMP frpt
min:
	CMP CL, BL
	JA above2
	JMP frpt
above2: MOV CL, BL
frpt: CMP ESP, EBP
	JE fin
	DEC ESP
	MOV [ESP], byte ptr CL
	JMP rpt
fin: OUTCHAR CL
EXIT
end start