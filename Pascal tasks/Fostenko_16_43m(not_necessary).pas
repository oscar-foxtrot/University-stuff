procedure DeleteLast(L:Tlist);
var n: Tlist;
begin
    if (L^.prev=nil) then L:=nil else
    if (L^.prev=L^.next) then begin dispose(L^.next); L^.prev:=nil; L^.next:=nil end else
    begin
        n:=L^.prev^.prev;
        dispose(n^.next);
        L^.prev:=n;
        n^.next:=nil;
    end;
end;