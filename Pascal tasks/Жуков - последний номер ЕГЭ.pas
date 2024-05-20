const N=60000;
var f:text;
i, g, counter1, counter2, a:longint;
product, productmax: real;
arr: array [1..20000, 1..300] of integer;

begin
  counter1:=1; counter2:=0;
  assign (f,'E:\Downloads\27-19b (1).txt');
  reset (f); readln (f);
  for i:=1 to N do begin
    readln (f, a);
    if a<>0 then begin
      counter2:=counter2+1; arr[counter1, counter2]:=a;
    end
    else
    begin counter1:=counter1+1; counter2:=0;
    end;
  end;
  close (f);
  
  for i:=1 to counter1 do
  begin
    g:=1;
    while arr[i, g] <> 0 do begin write(arr[i, g],' '); g:=g+1; end;
    writeln;
  end;
  
  productmax:=0;
  for i:= 1 to counter1 do
  begin
    g:=1; product:=1;
    while arr[i, g] <> 0 do begin product := product * arr[i,g]; g:=g+2 end;
    if product>productmax then productmax:=product;
    writeln (product);
  end;
  writeln;
  writeln (productmax);
end.