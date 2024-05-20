function Sum(L:Tlist):Real;
var min, max: Tlist;
minearlier: boolean;
summ: real;
begin
    min:=L; max:=L;
    L:=L^.next;
    while L<>nil do begin
        if min^.data<L^.data then begin
            min:=L;
            minearlier:=false;
        end
        else if max^.data>L^.data then begin
            max:=L;
            minearlier:=true;
        end;
        L:=L^.next;
    end;
    if max<>min then begin
        if minearlier then L:=min
            else begin L:=max; max:=min end;
        summ:=L^.data;
        repeat
            L:=L^.next;
            summ:=summ+L^.data;
        until L=max;
        Sum:=summ;
    end
    else Sum:=min^.data;
end;
