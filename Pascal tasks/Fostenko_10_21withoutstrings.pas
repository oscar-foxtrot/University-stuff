type co1 = '1'..'8';
co2 = 'a'..'h';
coordinates = 1..8;
var h: co2;
v: co1;
str,col: coordinates;
i,j: shortint;
begin
    read(h,v);
    str:= 8-ord(v)+ord(low(v));
    col:= ord(h)-ord(low(h))+1;
    for i:=1 to 8 do begin
        for j:=1 to 8 do
            if not((i=str) and (j=col)) and ((i=str) or (j=col) or (abs(i-str) = abs(col-j)))
            then write('*') else write('0');
        writeln;
    end;
end.
