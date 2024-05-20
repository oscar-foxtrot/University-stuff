const n=12;
type Tmatrix = array [1..n, 1..n] of integer;

function Equal(var A,B: Tmatrix): boolean;
var i,g: integer;
begin
    Equal:=true;
    for i:=1 to n do
        for g:=1 to n do if A[i,g]<>B[i,g] then begin
            Equal:=false; break;
        end;
    if Equal then exit else Equal:=true;
    for i:=1 to n do
        for g:=1 to n do if A[i,g]<>B[n-g+1,n-i+1] then begin
            Equal:=false; break;
        end;
    if Equal then exit else Equal:=true;
    for i:=1 to n do
        for g:=1 to n do if A[i,g]<>B[g,i] then begin
            Equal:=false; break;
        end;
    if Equal then exit else Equal:=true;
    for i:=1 to n do
        for g:=1 to n do if A[i,g]<>B[n-i+1,n-g+1] then begin
            Equal:=false; break;
        end;
end;

procedure ReadMatrix(var X: Tmatrix);
var a,b: integer;
begin
    for a:=1 to n do
        for b:=1 to n do read(X[a,b]);
end;

var A,B: Tmatrix;
begin
    ReadMatrix(A);
    ReadMatrix(B);
    write(Equal(A,B));
end.
