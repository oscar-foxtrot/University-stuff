INCLUDE settings.inc
INCLUDE io2020.inc
.CODE
start:
	ININT EAX
	c1: SHR EAX, 1
		JC c1
	CMP EAX, 0
	JZ yes
	OUTSTR <'Нет'>
	JMP fin
	yes: OUTSTR <'Да'>
	fin: EXIT
END start