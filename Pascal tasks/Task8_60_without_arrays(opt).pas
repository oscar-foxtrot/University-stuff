var
i: byte;
g, counter: integer;
s: longint;
begin
    s:=2;
    for i:=1 to 26 do begin
        counter:=0;
        for g:=0 to 999 do
            if (g div 100)+(g div 10 mod 10)+(g mod 10)=i then inc(counter);
        s:=s+sqr(counter);
    end;
    writeln(s);
end.
