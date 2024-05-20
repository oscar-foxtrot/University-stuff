procedure Addfirst(var L:Tlist; E:real);
var s: Tlist;
begin
    if L=nil then begin
        new(L);
        L^.data:=E;
        L^.next:=L;
    end
    else begin
        s:=L;
        while s^.next<>L do s:=s^.next;
        new(s^.next);
        s^.next^.data:=E;
        s^.next^.next:=L;
        L:=s^.next;
    end
end;
