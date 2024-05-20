procedure Create_List(N:integer; var L:Tlist);
var q: Tlist;
begin
    if N<=0 then begin L:=nil; exit end;
    new(q);
    L:=q;
    L^.data:=N;
    Create_List(N-1,L^.next);
end;