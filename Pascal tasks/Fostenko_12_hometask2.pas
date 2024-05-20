function minmaxdigit: byte;
function maxdigit(num: integer): byte;
var c,a: byte;
begin
    num:=abs(num);
    if num<=9 then maxdigit:=num;
    c:=num mod 10;
    a:=maxdigit(num div 10);
    if c<a then maxdigit:=a else maxdigit:=c;
end;
var num: integer;
mx: byte;
begin
    read(num);
    if num=0 then minmaxdigit:=0
        else begin
            mx:=maxdigit(num);
            if mx>minmaxdigit then minmaxdigit:=mx;
        end;

end;

begin
    minmaxdigit;
end.
