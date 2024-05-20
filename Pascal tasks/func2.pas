function f2(N: integer): longint;
begin
  if N<10 then f2:=2 else
  f2:=f2(N div 10)*10 + N mod 10;
end;

begin
  writeln(f2(1017));
end.