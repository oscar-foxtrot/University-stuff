var
x:real;
i,exponent: byte;
p: array [1..2] of byte;
m: array [1..9] of byte;
begin
    read(x);
    if x<0.1 then begin
        writeln (-1);
        halt;
    end;
    exponent:=0;
    while x>=1 do begin
        inc(exponent);
        x:=x/10;
    end;
    p[1]:=exponent div 10;
    p[2]:=exponent mod 10;
    for i:=1 to 9 do begin
        m[i]:=trunc(x*10);
        x:=frac(x*10);
    end;
    for i:=1 to 9 do write(m[i],' ');
    write(p[1],' ',p[2]);
end.