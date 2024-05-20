type Tfile = file of integer;
TTree = ^node; node = record right,left: TTree; data: integer; end;
procedure Build_Tree(var F:Tfile; var T:TTree);
procedure Position(var T:TTree; i:integer);
begin
    if T<>nil then
        if i<T^.data then Position(T^.left,i) else Position(T^.right,i)
            else begin new(T); T^.data:=i end
end;
var i: integer;
begin
    reset(F);
    if not(filesize(F)=0) then begin
        seek(F,filesize(F)-1);
        read(F,i);
        seek(F,filesize(F)-1);
        truncate(F);
        close(F);
        Position(T,i);
        Build_Tree(F,T);
    end else close(F);
end;

var F:Tfile;
T:TTree;
begin
  assign(F,'D:\TEST.txt');
  Build_Tree(F,T);
  write(T);
end.