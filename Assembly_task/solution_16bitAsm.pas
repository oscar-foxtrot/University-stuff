{INFORMATION ABOUT THE KEY:
The key is 4-byte. 2 higher bytes - Brand; the highest of 2 lower bytes
- year; the lowest byte - volume & the unit of volume measurement.

BRAND: consists of 16 bits: 4 higher bits contain a digit, then the two
6-bit cells each may contain either a digit or a letter. Alphabet is the next:
0 - ' ' (the cell is considered EMPTY although it contains "space"),
1 - '0', 2 - '1', ... , 10 - '9', 11 - 'A', ... , 36 - 'Z'
Example: Brand_1AC would be '0010 001011 001101'

YEAR: Is represented by 8 bits: the highest bit contains the information
about the century: '1' is for the 21st century and '0' is for the
20th century. Then the 7 lower bits is for storing the years within the
century. Thus the greater code corresponds to the greater year.
Example: 2002 would be '1 0000010'; 1990 would be '0 1011010'

VOLUME & UNITS: represented by 8 bits: the 7 higher bits contain the number
of full liters in the presented volume, then the last bit contains '1' if
the unit is gallons and '0' of the unit is liters. Because the volume is
an integer the code uniquely determines the volume either in litres
and gallons and is comparable (greater the volume - greater the code).
Example: 23 L would be '0010111 0'; 2 G would be a number greater than
7 liters but less than 8 => '0000111 1'

Thus 'Brand_1AC 1990 23 L' would be '0010001011001101 01011010 00101110'
END OF THE INTRODUCTION}


procedure inp(var key: longint);
{input 1 element of the array (packing included)}
procedure pack(var res: longint; var br: array of char;
var yr: array of char; volnum: byte; volmeas: char); assembler;
{$ASMMODE Intel}
asm
   PUSH AX
   PUSH BX
   PUSH DX
   PUSH DS

   XOR AX, AX  {DX:AX will be the result}
   MOV AL, volnum {res = brand(2bytes):year(1byte):volume(1byte)}
   SHL AL, 1
   CMP volmeas, 'G'
   JNE @nxt1
   INC AL
@nxt1: MOV DS, word ptr [yr+2]
   MOV BX, word ptr [yr]
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
   MOV DS, word ptr [res+2]
   MOV BX, word ptr [res]
   MOV word ptr [BX], AX {res = _ _ AX}
   MOV DS, word ptr [br+2]
   MOV BX, word ptr [br]
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
   JE @fin1
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
@fin1: MOV DS, word ptr [res+2]
   MOV BX, word ptr [res]
   MOV word ptr [BX+2], DX

   POP DS
   POP DX
   POP BX
   POP AX
end;
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
          read(c);
    until (c=' ');
    for i:=1 to (3-cnt) do begin
        for g:=cnt downto 1 do BR[g+i]:=BR[g+i-1];
        BR[i]:=' ';
    end;
    read(c);
    for i:=1 to 3 do read(YR[i]); read(c);
    read(vol1.number); read(c);
    read(vol1.measure);
    read(c); {ignore space (1 character)}
    if vol1.measure='G' then vol1.number:=trunc(vol1.number*3.7854);
    pack(key, BR, YR, vol1.number, vol1.measure)
end;

procedure printkey(key: longint); assembler;
{$ASMMODE Intel}
asm
   PUSH AX
   PUSH BX
   PUSH CX
   PUSH DX
   MOV AH, 02h
   MOV BX, word ptr [key+2]
   MOV CX, 16
   XOR DL, DL
@lb1: SHL BX, 1
   ADC DL, '0'
   INT 21h  {func 02h}
   XOR DL, DL
   LOOP @lb1
   MOV BX, word ptr [key]
   MOV CX, 16
   XOR DL, DL
@lb2: SHL BX, 1
   ADC DL, '0'
   INT 21h  {func 02h}
   XOR DL, DL
   LOOP @lb2
   POP DX
   POP CX
   POP BX
   POP AX
end;

procedure outp(key: longint);
{unpack and display an element}
procedure unpack(key: longint; var br: array of char;
var yr: word; var volume:byte; var measure: char); assembler;
{$ASMMODE Intel}
asm
   PUSH DS
   PUSH AX
   PUSH BX
   PUSH DX
   PUSH DI
   PUSH CX

   MOV AX, word ptr [key+2] {brand}
   MOV DS, word ptr [br+2]
   MOV BX, word ptr [br]
   MOV DX, AX
   SHR DX, 12
   CMP DL, 0
   JNE @lb1
   MOV byte ptr [BX], ' '
   JMP @lbl1
@lb1: ADD DL, ('0'-1)
   MOV byte ptr [BX], DL
@lbl1: MOV CX, 12
@nxt1: SUB CX, 6
   INC BX
   MOV DX, AX
   MOV DI, 003Fh
   SHL DI, CL
   AND DX, DI
   SHR DX, CL
   CMP DL, 0
   JNE @lb2
   MOV byte ptr [BX], (' ')
   JMP @nxt2
@lb2: CMP DL, 10
   JA @op2
   ADD DL, ('0'-1)
   MOV byte ptr [BX], DL
   JMP @nxt2
@op2: ADD DL, ('A'-11)
   MOV byte ptr [BX], DL
@nxt2: CMP CL, 0
   JNE @nxt1

   MOV AX, word ptr [key]   {year}
   MOV DS, word ptr [yr+2]
   MOV BX, word ptr [yr]
   XOR DX, DX
   CMP AH, 80h
   JA @opt2
   ADD DX, 1900
   JMP @nxt3
@opt2: ADD DX, 2000
@nxt3: AND AH, 01111111b
   SHR AX, 8
   ADD DX, AX
   MOV word ptr [BX], DX

   MOV AL, byte ptr [key]       {volume&measure}
   MOV DS, word ptr [measure+2]
   MOV BX, word ptr [measure]
   SHR AL, 1
   JC @oopt2
   MOV word ptr [BX], 'L'
   JMP @nxt4
@oopt2: MOV word ptr [BX], 'G'
@nxt4: MOV DS, word ptr [volume+2]
   MOV BX, word ptr [volume]
   MOV byte ptr [BX], AL

   POP CX
   POP DI
   POP DX
   POP BX
   POP AX
   POP DS
end;
var br: array [1..3] of char;
year: word; volume, i: byte; measure: char;
begin
    unpack(key, br, year, volume, measure);
    if measure='G' then volume:=round(volume/3.7854);
    write('Brand_');
    for i:=1 to 3 do if (br[i]<>' ') then write(br[i]);
    write(' ',year,' ',volume,' ',measure);
end;

procedure sort(karr: array of longint; sizekarr: integer);
assembler; {done in O(n squared)}
{$ASMMODE Intel}
asm
   PUSH DS
   PUSH CX
   PUSH AX
   PUSH BX
   PUSH SI

   XOR CX, CX
   MOV DS, word ptr [karr+2]
   MOV DX, word ptr [karr]
   MOV CX, 4
@lb1: MOV BX, word ptr [karr]
   ADD BX, CX
@lp1: CMP BX, DX
   JE @nxt1
   MOV AL, byte ptr [BX]
   SUB BX, 4
   CMP AL, byte ptr [BX]
   JAE @nxt1
   MOV AX, word ptr [BX]
   MOV SI, word ptr [BX+2]
   MOV word ptr [BX+4], AX
   MOV word ptr [BX+6], SI
   JMP @lp1
@nxt1: ADD CX, 4
   CMP CX, sizekarr
   JNE @lb1

   POP SI
   POP BX
   POP AX
   POP CX
   POP DS
end;


const n=1;
var
keys: array [1..n] of longint; {4-byte (dword) key}
i: word;
begin
    for i:=1 to n do inp(keys[i]);
    sort(keys, sizeof(keys));
    for i:=1 to n do begin outp(keys[i]); write(' '); end;
end.
