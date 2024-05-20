type month= 1..12;
day= 1..31;
var d:day;
m: month;
y: integer;

begin
    read(d, m, y);
    if d=1 then begin
        if m<>1 then dec(m)
        else begin
            m:=12;
            dec(y);
        end;
        case m of
            1,3,5,7,8,10,12: d:=31;
            4,6,9,11: d:=30;
            else if (y mod 4 = 0) and ((y mod 100 <> 0) or (y mod 400 = 0)) then d:=29
                 else d:=28
        end;
    end
    else dec(d);
    write(d,' ',m,' ',y);
end.
