XOR EAX, EAX
lp0: MOV EDI, EAX	;It is convenient to use "string" operations, but the topic awaits further
lp1: ADD EDI, (type stud)
	MOV ECX, (20)
lp1rpt0: MOV DL, gr[EAX].name[ECX-1]
	CMP DL, gr[EDI].name[ECX-1]
	JNE jlp1
	loop lp1rpt0
	OUTCHAR '1'
	JMP fin1
jlp1: CMP EDI, (type stud)*(N-1)
	JNE lp1
	ADD EAX, (type stud)
	CMP EAX, (type stud)*(N-1)
	JE fin0
	JMP lp0
fin0: OUTCHAR '0'
fin1: