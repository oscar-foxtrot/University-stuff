function Value(var F:Tfc): boolean;
var v1,v2,oper: char;
i: byte;
begin
    Setemptys(s);
    reset(F);
    while not eof(F) do begin
        read(F,v1);
        if v1='f' then begin for i:=1 to 4 do read(F,v1); Pushs(S,'0') end
        else if v1='t' then begin for i:=1 to 3 do read(F,v1); Pushs(S,'1') end
        else if v1='a' then begin for i:=1 to 2 do read(F,v1); Pushs(S,'*') end
        else if v1='n' then begin for i:=1 to 2 do read(F,v1); Pushs(S,'-') end
        else if v1='o' then begin read(F,v1); Pushs(S,'+') end
        else if v1=')' then begin
            pops(s,v1); pops(s,oper);
            if oper='-' then if v1='0' then v1:='1' else v1:='0' else
            begin
                pops(s,v2);
                if (oper='+') then if (v1='1') or (v2='1') then v1:='1' else v1:='0'
                    else if (v1='0') or (v2='0') then v1:='0' else v1:='1';
            end;
            pops(S,oper);
            Pushs(s,v1);
        end
        else if v1<>' ' then Pushs(S,v1);
    end;
    close(F);
    pops(s,v1);
    Value:=v1='1';
end;