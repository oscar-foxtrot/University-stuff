var
i: byte;
g, counter: integer;
s: array [0..27] of integer;
sum: longint;
begin
    s[0]:=1;
    s[27]:=1;
    for i:=1 to 26 do s[i]:=0;
    for i:=1 to 26 do
        for g:=0 to 999 do
            if (g div 100)+(g div 10 mod 10)+(g mod 10)=i then inc(s[i]);
    sum:=0;
    for i:=0 to 27 do sum:=sum+sqr(s[i]);
    writeln(sum);
end.
