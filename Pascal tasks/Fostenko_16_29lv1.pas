procedure Delete_same(L:Tlist);
var alreadyin: set of real;
p,tempptr: Tlist;
begin
    p:=L;
    alreadyin:=[p^.data];
    while p<>nil do begin
        if p^.next^.data in alreadyin then
            if p^.next^.next<>nil then begin
                tempptr:=p^.next;
                p^.next:=p^.next^.next;
                dispose(tempptr);
            end
            else begin
                dispose(p^.next);
                p^.next:=nil;
            end
        else alreadyin:=alreadyin+[p^.next^.data];
        p:=p^.next;
    end;
end;
