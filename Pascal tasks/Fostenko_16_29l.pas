procedure Delete_Same(L:Tlist);
var p,s,tmp:Tlist;
alreadyin: boolean;
begin
    if L=nil then exit;
    s:=L;
    while L^.next<>nil do begin
        p:=s;
        alreadyin:=false;
        while p<>L^.next do begin
            if p^.data=L^.next^.data then begin
                alreadyin:=true;
                break;
            end;
            p:=p^.next;
        end;
        if alreadyin then begin
            tmp:=L^.next;
            L^.next:=L^.next^.next;
            dispose(tmp);
        end
        else L:=L^.next;
    end;
end;
