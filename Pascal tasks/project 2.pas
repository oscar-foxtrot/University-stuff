Program Fostenko2;
const N=20;
var YY,XX:array [1..N] of integer;
k,i:shortint;
begin
  i:=0;
  Write ('Массив 1(YY): ');
  Randomize;
  for k:=1 to N do begin 
  YY[k]:=random(31)-1; 	{-1 to 29}
  Write (YY[k],' ');
  end;
  
  Writeln;
  Write ('Массив 2(XX): ');
  for k:=1 to N do if (YY[k]>=10) then 
  begin
    i:=i+1;
    XX[i]:=YY[k];
    Write (XX[i],' ');
    end;

end.