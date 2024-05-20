type numwmdigit = record
    num: integer;
    mx: byte;
end;
function minmaxdigit: numwmdigit;
function maxdigit(num: integer): byte;
var c,a: byte;
begin
    num:=abs(num);
    if num<=9 then begin maxdigit:=num; exit end;
    c:=num mod 10;
    a:=maxdigit(num div 10);
    if c<a then maxdigit:=a else maxdigit:=c;
end;
var nm, recurnm: numwmdigit;
begin
    read(nm.num);
    if nm.num=0 then begin
        nm.mx:=0;
        minmaxdigit:=nm;
    end
    else begin
        nm.mx:=maxdigit(nm.num);
        recurnm:=minmaxdigit;
        if (nm.mx<=recurnm.mx) or (recurnm.num=0) then minmaxdigit:=nm else minmaxdigit:=recurnm;
    end;
end;

begin
    write(minmaxdigit.num);
end.
