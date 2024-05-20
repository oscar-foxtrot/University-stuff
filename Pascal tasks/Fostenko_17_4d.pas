function Value(var F:Tfc): boolean;
var c: char;
tmp: char;
i: byte;
begin
    Setemptys(s);
    reset(F);
    while not eof(F) do begin
        read(F,c);
        if c='f' then begin for i:=1 to 4 do read(F,c); Pushs(S,'0') end
        else if c='t' then begin for i:=1 to 3 do read(F,c); Pushs(S,'1') end
        else if c='a' then begin for i:=1 to 2 do read(F,c); Pushs(S,'*') end
        else if c='n' then begin for i:=1 to 2 do read(F,c); Pushs(S,'-') end
        else if c='o' then begin read(F,c); Pushs(S,'+') end
        else if c=')' then begin
            pops(s,c);
            if c='1' then begin
                pops(s,tmp);
                if tmp='-' then c:='0' else
                if tmp='+' then begin c:='1'; pops(s,tmp) end else
                begin
                    pops(s,c);
                    if c='1' then c:='1' else c:='0';
                end;
            end
            else if c='0' then begin
                pops(s,tmp);
                if tmp='-' then c:='1' else
                if tmp='*' then begin c:='0'; pops(s,tmp) end else
                begin
                    pops(s,c);
                    if c='1' then c:='1' else c:='0';
                end;
            end;
            pops(s,tmp);
            pushs(s,c);
        end
        else if c<>' ' then Pushs(S,c);
    end;
    close(F);
    pops(s,c);
    Value:=c='1';
end;