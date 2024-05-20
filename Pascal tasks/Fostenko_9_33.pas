const n=2;
var A: array [1..n, 1..n] of real;
B,X : array [1..n] of real;
i,g:integer;
coef:real;
begin
    for i:=1 to n do begin
        for g:=1 to n do
            if g<i then A[i,g]:=0 else read(A[i,g]);
        read(B[i])
    end;
    for i:=n downto 1 do begin
        coef:=0;
        for g:=i to n do coef:=coef+X[g]*A[i,g];
        X[i]:=(B[i]-coef)/A[i,i];
    end;
    for i:=1 to n do write(X[i],' ');
end.