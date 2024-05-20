type consonants1 = set of 'c'..'x';
const M = ['c','f','h','k','p','q','s','t','x'];
var L,E,UE: consonants1;
c: char;
even, twocommas, oneword: boolean;
begin
    even:=false;
    oneword:=true;
    E:= [];
    UE:= M;
    while true do begin
        L:=[];
        read(c);
        if ((c=',') or (c='.'))
            then begin write('Error'); halt end;
        while (c<>',') and (c<>'.') do begin
            if (c<'a') or (c>'z')
                then begin write('Error'); halt end;
            if c in M then L:=L+[c];
            read(c);
        end;
        if even then E:=E+(M-L) else
        UE:=UE*L;
        if c='.' then break;
        even:=even xor true;
        oneword:=false;
    end;
    if oneword then L:=UE else L:=E*UE;
    for c:='c' to 'x' do if c in L then write(c);
end.
