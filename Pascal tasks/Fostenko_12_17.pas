procedure InAndOut;
var c: integer;
begin
    read(c);
    if c<0 then begin
        write(c,' ');
        InAndOut;
    end
    else if c>0 then begin
        InAndOut;
        write(c,' ');
    end;
end;

begin
    InAndOut;
end.