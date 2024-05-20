var k, b: int64;
counter, i: integer;
begin
    read(k);
    if k<0 then begin
            write('-'); k:=abs(k);
        end;
    b:=k;
    counter:=0;
    while b<>0 do
    begin
        inc(counter);
        b:=b div 10;
    end;
    b:=1;
    for i:=1 to counter-1 do b:=b*10;
    while b<>0 do
    begin
        write(chr(ord('0')+k div b));
        k:=k-(k div b * b);
        b:=b div 10;
    end;
end.
