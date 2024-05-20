function One_child(T:TTree):integer;
begin
    if (T^.left=nil) and (T^.right=nil) then One_child:=0 else
    if (T^.left=nil) and (T^.right<>nil) then One_child:=1+One_child(T^.right) else
    if (T^.left<>nil) and (T^.right=nil) then One_child:=1+One_child(T^.left) else
        One_child:=One_child(T^.left)+One_child(T^.right)
end;