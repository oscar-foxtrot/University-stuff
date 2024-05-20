include settings.inc
include io2020.inc


M=?
N=?

.DATA
A db M dup (?)
B dB N dup (?)
K db ?

.CODE
F PROC
    PUSH ECX
    XOR AL, AL
    CYCLE:
        DEC ECX
        
        CMP BYTE PTR [ESI][ECX], BL
        JNZ L1
            INC AL
        L1:
            CMP ECX, 0    
            JNZ CYCLE
    POP ECX
RET
F ENDP

START:
    XOR ECX, ECX
c1: ININT byte ptr A[ECX]
	INC ECX
	CMP ECX, M
	JNZ c1

    XOR ECX, ECX
c2: ININT byte ptr B[ECX]
	INC ECX
	CMP ECX, N
	JNZ c2
	
	ININT K
	
    LEA ESI, B
    MOV ECX, N
    MOV BL, K
    CALL F

    LEA ESI, A
    MOV ECX, M
    MOV BL, AL
    CALL F
    
    OUTU AL
EXIT
END START