procedure pack(var res: longint; var br: array of char;
var yr: array of char; volnum: byte; volmeas: char); assembler;
asm
   PUSH AX
   PUSH BX
   PUSH DX

   XOR AX, AX  {DX:AX will be the result}
   MOV AL, volnum {res = brand(2bytes):year(1byte):volume(1byte)}
   SHL AL, 1
   CMP volmeas, 'G'
   JNE @nxt1
   INC AL
@nxt1: MOV DS, word ptr yr+2
   MOV BX, word ptr yr
   MOV AH, byte ptr [BX]
   SUB AH, '0'
   JNZ @nxt2
   OR AH, 10000000b
   JMP @lbl3
@nxt2: XOR AH, AH
@lbl3: MOV DL, byte ptr [BX+1] {make a number from 2 characters}
   SUB DL, '0'
   SHL DL, 1
   ADD AH, DL {N*10 = N*(8+2) = 8*N + 2*N}
   SHL DL, 2
   ADD AH, DL
   MOV BL, byte ptr [BX+2]
   SUB BL, '0'
   ADD AH, BL
   MOV DS, word ptr res+2
   MOV BX, word ptr res
   MOV word ptr [BX], AX {res = _ _ AX}
   MOV DS, word ptr br+2
   MOV BX, word ptr br
   XOR DX, DX
   MOV DL, byte ptr [BX+2]
   CMP DL, 'A'
   JB @opt2
   CMP DL, 'Z'
   JA @opt2
   SUB DL, ('A'-11)
   JMP @nxt3
@opt2: SUB DL, ('0'-1)
@nxt3: XOR AX, AX
   MOV AL, byte ptr [BX+1]
   CMP AL, ' '
   JMP @fin1
   CMP AL, 'A'
   JB @opt2a
   CMP AL, 'Z'
   JA @opt2a
   SUB AL, ('A'-11)
   JMP @nxt4
@opt2a: SUB AL, ('0'-1)
@nxt4: SHL AX, 6
   OR DX, AX
   MOV AL, byte ptr [BX]
   CMP AL, ' '
   JE @fin1
   SUB AL, ('0'-1)
   SHL AX, 12
   OR DX, AX
   MOV DS, word ptr res+2
   MOV BX, word ptr res
   MOV word ptr [BX+2], DX

@fin1:
   POP DX
   POP BX
   POP AX
end;

procedure inp; {input 1 element of the array (packing included)}
var c: char;
BR, YR: array [1..3] of char;
type VOL = record
    number: byte;
    measure: char;
end;
var vol1: VOL;
cnt, i, g: byte;
begin
    for i:=1 to 6 do read(c);
    cnt:=0;
    read(c);
    repeat
          inc(cnt);
          BR[cnt]:=c;
          read(c)
    until c=' ';
    for i:=1 to (3-cnt) do begin
        for g:=cnt downto 1 do BR[g+i]:=BR[g+i-1];
        BR[i]:=' ';
    end;
    read(c); read(c);
    for i:=1 to 3 do read(YR[i]);
    read(c);
    read(vol1.number); read(vol1.measure);
    read(c); {ignore space (1 character)}
    if vol1.measure='G' then vol1.number:=trunc(vol1.number*3.7854);
    pack



keys: array [1..n] of longint; //4-byte key
begin

end.
