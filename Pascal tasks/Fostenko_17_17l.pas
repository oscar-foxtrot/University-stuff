procedure Delete_Minimal(var T:TTree);
var tmp:TTree;
begin
    if T^.left<>nil then if T^.left^.left<>nil then Delete_Minimal(T^.left)
        else if T^.left^.right<>nil then begin
            tmp:=T^.left^.right;
            dispose(T^.left);
            T^.left:=tmp;
        end else begin dispose(T^.left); T^.left:=nil end
    else begin tmp:=T^.right; dispose(T); T:=tmp; end;
end;