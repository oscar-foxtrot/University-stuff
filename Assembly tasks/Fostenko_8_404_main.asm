;MAIN mod.
INCLUDE settings.inc
INCLUDE io2020.inc
.STACK 4096

EXTRN STRINPUTP@0: near, APPLY_RULE1P@0: near, APPLY_RULE2P@0: near ;type "proc" also works

.DATA
	str1 DB 201 DUP (0) ;additional 100 is required for the rule application (double a symbol etc.). Not necessary if the modified text is not stored
	str2 DB 201 DUP (0) ; "0" is the sign of the end (1 additional byte to the maximum length of 200)
	
.CODE
	
	STRINPUT MACRO stri 	; Passing parameters to the "STRINPUT" procedure. ECX register changes to the length of the string
		PUSH EAX
		PUSH dword ptr (offset stri)
		CALL STRINPUTP@0
		CMP AL, 0FFh
		POP EAX
		JE finerr 		; Error? -> Terminate and display an "Error" message
	ENDM

	APPLY_RULE1 MACRO source
		PUSH dword ptr (offset source)
		CALL APPLY_RULE1P@0
	ENDM
	
	APPLY_RULE2 MACRO source, len
		PUSH dword ptr len
		PUSH dword ptr (offset source)
		CALL APPLY_RULE2P@0
	ENDM
	
start:
	;OUTSTR <'Введите текст №1: '>
	STRINPUT str1
	;NEWLINE
	MOV EDX, ECX
	INCHAR AL ;It seems like there are some unnecessary characters between the entered strings
	INCHAR AL ;Two "INCHAR" instructions are to ignore those characters
	;OUTSTR <'Введите текст №2: '>
	STRINPUT str2
	;NEWLINE
	CMP EDX, ECX
	JAE opt1 
	APPLY_RULE1 (offset str2)
	APPLY_RULE2 (offset str1), EDX
	JMP nxt1
opt1: APPLY_RULE2 (offset str2), ECX
	APPLY_RULE1 (offset str1)
	
nxt1: LEA ESI, str1
outp1: LODSB
	CMP AL, 0
	JE nxt2
	OUTCHAR AL
	JMP outp1
nxt2: LEA ESI, str2
	NEWLINE
outp2: LODSB
	CMP AL, 0
	JE fin
	OUTCHAR AL
	JMP outp2
	
fin: NEWLINE
	EXIT
finerr: NEWLINE
	OUTSTR <'������'>
	EXIT
END start