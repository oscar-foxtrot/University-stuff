const n=2;
type Tmatrix=array [1..n, 1..n] of real;

function Trace (var a: Tmatrix): real;
var i,g: byte;
trc: real;
begin
    trc:=a[1,1];
    for i:=2 to n do trc:=trc+a[i,i];
    Trace:=trc;
end;

procedure readmatrix (var a: Tmatrix);
var i,g: byte;
mtrx: byte;
begin
    for i:=1 to n do
        for g:=1 to n do read(a[i,g]);
end;

procedure WriteMatrixSquare (var a: Tmatrix);
var i,g,k: byte;
squaredmtx: Tmatrix;
begin
    for i:=1 to n do begin
        for g:=1 to n do begin
            squaredmtx[i,g]:=0;
            for k:=1 to n do squaredmtx[i,g]:=squaredmtx[i,g]+a[i,k]*a[k,g];
            write(squaredmtx[i,g],' ');
        end;
        writeln;
    end;
end;

var matrices: array [1..2] of Tmatrix;
begin
    readmatrix(matrices[1]);
    readmatrix(matrices[2]);
    if Trace(matrices[2])<Trace(matrices[1]) then WriteMatrixSquare(matrices[2])
        else WriteMatrixSquare(matrices[1]);
end.
