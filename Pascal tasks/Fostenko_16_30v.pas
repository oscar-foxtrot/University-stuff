function Max(L:Tlist): real;
var t:real;
begin
    if L^.next=nil then Max:=L^.data
        else begin
            t:=Max(L^.next);
            if t<=L^.data then Max:=L^.data
                else Max:=t;
        end
end;