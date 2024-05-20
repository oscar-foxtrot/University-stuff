procedure Create(var T:TTree; n: integer);
procedure Fill(var T:TTree);
begin
    if T<>nil then begin
        T^.data:=T^.data+1;
        Fill(T^.right);
        Fill(T^.left);
    end;
end;
var p:TTree;
i:integer;
begin
    if n<=0 then T:=nil else
    begin
        new(T);
        Create(T^.right,n-1);
        Create(T^.left,n-1);
        T^.data:=1;
        if T^.right<>nil then begin
            Fill(T^.right);
            Fill(T^.left);
        end;
    end;
end;
