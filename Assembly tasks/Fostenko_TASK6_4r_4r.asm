;VARIANT 20 => 4th rule from the 1st list, 4th rule from the 2nd list. Corresponds to number 404 of the task in the PROGRAM TESTING SYS.
INCLUDE settings.inc
INCLUDE io2020.inc
.STACK 4096
.DATA
	str1 DB 201 DUP (0) ;additional 100 is required for the rule application (double a symbol etc.). Not necessary if the modified text is not stored
	str2 DB 201 DUP (0) ; "0" is the sign of the end (1 additional byte to the maximum length of 200)
.CODE

	STRINPUTP PROC
		PUSH EBP			; Parameters are passed through STACK: (EBP+8) - offset (String); EAX register is for the return codes, ECX is changed to store the length of the string
		MOV EBP, ESP		; RETURNS CODE 0FFh in case of an ERROR, RETURNS CODE 0 in case WITHOUT ERRORS (AL register)
		PUSH EDI			; RETURNS the LENGTH of the string (ECX register)
		MOV EDI, [EBP+8]
		INCHAR AL
		CMP AL, '.'	
		JZ sterr1
		XOR ECX, ECX
	stlp1: MOV byte ptr [EDI][ECX], AL
		INC ECX
		INCHAR AL
		CMP AL, '.'
		JZ stnxt1
		CMP ECX, 100
		JZ sterr1
		JMP stlp1
	sterr1: MOV AL, -1
		JMP stfin
	stnxt1: XOR AL, AL
	stfin: POP EDI
		POP EBP
		RET 4
	STRINPUTP ENDP

	STRINPUT MACRO stri 	; Passing parameters to the "STRINPUT" procedure. ECX register changes to the length of the string
		PUSH EAX
		PUSH dword ptr (offset stri)
		CALL STRINPUTP
		CMP AL, 0FFh
		POP EAX
		JE finerr 		; Error? -> Terminate and display an "Error" message
	ENDM
	
	APPLY_RULE1 PROC ;Parameters are passed through STACK: (EBP+8) - offset (String). Registers are not modified.
		PUSH EBP
		MOV EBP, ESP
		PUSH EAX
		PUSH ECX
		PUSH EBX
		XOR ECX, ECX
		MOV EBX, [EBP+8]
	aplp2: INC ECX
		MOV AL, byte ptr [EBX][ECX-1]
		CMP AL, 0
		JNE apnxt2
		POP EBX
		POP ECX
		POP EAX
		POP EBP
		RET 4
	apnxt2: CMP AL, 'A'
		JB aplp2
		CMP AL, 'Z'
		JA aplp2
		CMP AL, 'Z'
		JE apopt2
		INC AL
		MOV byte ptr [EBX][ECX-1], AL
		JMP aplp2
	apopt2: MOV byte ptr [EBX][ECX-1], 'A'
		JMP aplp2
	APPLY_RULE1 ENDP
	
	APPLY_RULE2 PROC ;Parameters are passed through STACK: (EBP+8) - offset (String), (EBP+12) - length (String). Registers are not modified.
		PUSH EBP
		MOV EBP, ESP
		PUSH ECX
		PUSH EDX
		PUSH EDI
		PUSH EAX
		PUSH EBX
		MOV ECX, [EBP+12]
		MOV EDX, ECX
		MOV EDI, [EBP+8]
	lbl1: CMP byte ptr [EDI][ECX-1], '0'
		JB rp1
		CMP byte ptr [EDI][ECX-1], '9'
		JA rp1
		MOV EAX, EDX
		INC EAX
	rp2: DEC EAX
		MOV BL, byte ptr [EDI][EAX-1]
		MOV byte ptr [EDI][EAX], BL
		CMP EAX, ECX
		JNE rp2
		INC EDX
	rp1: LOOP lbl1
		POP EBX
		POP EAX
		POP EDI
		POP EDX
		POP ECX
		POP EBP
		RET 8
	APPLY_RULE2 ENDP
	
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
	PUSH dword ptr (offset str2)
	CALL APPLY_RULE1 ;str1 - 2nd rule, str2 - 1st rule
	PUSH EDX
	PUSH dword ptr (offset str1)
	CALL APPLY_RULE2
	JMP nxt1
opt1: PUSH ECX
	PUSH dword ptr (offset str2)
	CALL APPLY_RULE2 ;str1 - 1st rule, str2 - 2nd rule
	PUSH dword ptr (offset str1)
	CALL APPLY_RULE1
	
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
	OUTSTR <'Ошибка'>
	EXIT
END start