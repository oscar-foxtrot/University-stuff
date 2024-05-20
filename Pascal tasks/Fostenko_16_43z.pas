procedure Add_Last(L:Tlist; E:real);
var s:Tlist;
begin
    if L^.next<>nil then begin
        s:=L^.prev;
        new(s^.next);
        s:=s^.next;
        with s^ do begin
            next:=nil;
            prev:=L^.prev;
            data:=E;
        end;
        L^.prev:=s;
    end else begin  //given that L is already a list with a header node
        new(L^.next);
        L^.prev:=L^.next;
        L^.next^.data:=E;
    end;

end;
