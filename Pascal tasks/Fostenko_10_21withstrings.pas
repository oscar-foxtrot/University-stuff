type co1 = '1'..'8';
co2 = 'a'..'h';
var h: co2;
v: co1;
i,j: byte;
begin
    read(h,v);
    for i:=ord(high(v)) downto ord(low(v)) do begin
        for j:=ord(low(h)) to ord(high(h)) do
            if not((i=ord(v)) and (j=ord(h))) and ((i=ord(v)) or (j=ord(h)) or (abs(ord(v)-i)=abs(j-ord(h))))
            then write('*') else write('0');
        writeln;
    end;
end.