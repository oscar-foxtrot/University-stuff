const n=1;
m=1;
var A: array [1..n, 1..m] of integer;
b: array [1..n] of boolean;
i,g: integer;
symmetric: boolean;
begin
    for i:=1 to n do begin
        symmetric:=true;
        for g:=1 to m do read(A[i,g]);
        for g:=1 to m div 2 do
            if A[i,g]<>A[i,m-g+1] then begin
                symmetric:=false;
                break
            end;
        b[i]:=symmetric;
        write(b[i],' ')
    end;
end.