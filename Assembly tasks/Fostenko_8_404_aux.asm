;AUXILIARY mod.
INCLUDE settings.inc
INCLUDE io2020.inc
.STACK 4096
PUBLIC STRINPUTP, APPLY_RULE1P, APPLY_RULE2P
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
	
	APPLY_RULE1P PROC ;Parameters are passed through STACK: (EBP+8) - offset (String). Registers are not modified.
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
	APPLY_RULE1P ENDP
	
	APPLY_RULE2P PROC ;Parameters are passed through STACK: (EBP+8) - offset (String), (EBP+12) - length (String). Registers are not modified.
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
	APPLY_RULE2P ENDP
		
END