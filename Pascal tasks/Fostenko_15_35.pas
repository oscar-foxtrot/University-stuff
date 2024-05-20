function Same(var F:TString):Boolean;
var s: set of char;

function notin:Boolean;
var c:char;
begin
    if not eof(F) then begin
        read(F,c);
        if c in s then begin notin:=false; exit end
        else s:=s+[c];
    end;
end;


begin
    reset(F);
    s:=[];
    same:=notin;
    close(F);
end;
