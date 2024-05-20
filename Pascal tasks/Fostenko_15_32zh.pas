procedure Delete(var F:Tstring);
var c: char;
begin
    reset(F);
    if FileSize(F)>=2 then begin
        seek(F,FileSize(F)-1);
        read(F,c);
        seek(F,FileSize(F)-2);
        write(F,c);
        truncate(F);
    end;
    close(F);
end;