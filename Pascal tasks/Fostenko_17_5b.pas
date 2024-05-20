procedure Output_pos(var F:Tfc);
var i,g: integer;
c: char;
begin
    reset(F);
    setemptys(s);
    i:=0;
    while not eof(F) do begin
        read(F,c);
        inc(i);
        if c='(' then pushs(s,i) else
        if c=')' then begin
            pops(s,g);
            write('(',g,' ',i,')',' ');
        end;
    end;
    close(F);
end;