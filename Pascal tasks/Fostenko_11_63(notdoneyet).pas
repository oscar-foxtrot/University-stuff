const n=12;
type Tmatrix = array [1..n, 1..n] of integer;

procedure ReadMatrix(var X: Tmatrix);
var a,b: integer;
begin
    for a:=1 to n do
        for b:=1 to n do read(X[a,b]);
end;

function Equal(var A,B: Tmatrix): boolean;
var i,g: integer;
begin
    for i:=1 to n do
        for g:=1 to n do if A[i,g]<>B[i,g] then begin
            Equal:=false;
            exit;
        end;
    Equal:=true;
end;

function MirroredAntiDiag (var X: Tmatrix): TMatrix;
var i,g,temp: integer;
begin
    for i:=1 to n do
        for g:=1 to n do if i+g<n+1 then begin
            temp:=X[i,g];
            X[i,g]:=X[n-g+1,n-i+1];
            X[n-g+1,n-i+1]:=temp;
        end;
    MirroredAntiDiag:=X;
end;

function MirroredMainDiag (var X: Tmatrix): TMatrix;
var i,g,temp: integer;
begin
    for i:=1 to n do
        for g:=1 to n do if i<g then begin
            temp:=X[i,g];
            X[i,g]:=X[g,i];
            X[g,i]:=temp;
        end;
    MirroredMainDiag:=X;
end;

var A,B: Tmatrix;
i,g: integer;
begin
    ReadMatrix(A);
    ReadMatrix(B);
    write(Equal(A,B) or Equal(A,MirroredMainDiag(B)) or Equal(A,MirroredAntiDiag(B)));
end.
