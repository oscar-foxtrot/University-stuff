const
n=1;
nfibo=23;
var
a: array [1..n] of integer;
fibo: array [1..nfibo] of integer;
var i,g,counter:integer;
begin
    for i:=1 to n do read(a[i]);
    fibo[1]:=1; fibo[2]:=1;
    for i:=3 to nfibo do fibo[i]:=fibo[i-2]+fibo[i-1];
    counter:=0;
    for i:=1 to n do
        for g:=2 to nfibo do if a[i]=fibo[g] then begin
            inc(counter);
            break;
        end;
    writeln(counter);
end.