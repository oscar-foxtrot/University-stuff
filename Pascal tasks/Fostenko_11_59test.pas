const eps=1E-9;
function Powers(X,A:real): real;
var curterm,taylor: real;
i: integer;
begin
    curterm:=1;
    i:=0;
    taylor:=1;
    while abs(curterm)>=eps do begin
        inc(i);
        curterm:=curterm*(X-1)*(A-(i-1))/i;
        taylor:=taylor+curterm;
    end;
    Powers:=taylor;
end;

var t:real;
begin
    write(Powers(0,0))
    //read(t);
    //write( Power(1-Power(cos(t),4)/4, 1/4) + (1+Power(arctan(t)/2, 1/5))*Power(1/(3+Power(t,2)), 1/9) );
end.
