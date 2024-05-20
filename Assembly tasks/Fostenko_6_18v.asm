MOV ECX, N
MOV EDX, offset A
lp0: CMP [EDX][ECX*2-2], word ptr 0
	JG lp1
	loop lp0
lp1: CMP ECX, 0
	JE tfin
	MOV [EDX][ECX*2-2], word ptr -1
tfin: