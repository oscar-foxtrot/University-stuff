type complex=record Re,Im: real end;
procedure chTaylor(var z: complex);
const eps = 1E-6;
var s,cur: complex;
temp,fact: real;
begin
  s:=z;
  fact:=2;
  cur.Re:=1;
  s.Re:=1;
  while (sqr(cur.Re)+sqr(cur.Im))>=sqr(eps) do begin
    temp:=(cur.Re*sqr(z.Re)-cur.Re*sqr(z.Im)-2*cur.Im*z.Re*z.Im)/fact;
    cur.Im:=(2*cur.Re*z.Re*z.Im+cur.Im*sqr(z.Re)-cur.Im*sqr(z.Im))/fact;
    cur.Re:=temp;
    s.Re:=s.Re+cur.Re;
    s.Im:=s.Im+cur.Im;
    fact:=fact*(fact+1)*(fact+2);
  end;
  z:=s;
end;

var z: complex;
begin
  read(z.Re,z.Im);
  chTaylor(z);
  writeln(z.Re,' ',z.Im);
end.