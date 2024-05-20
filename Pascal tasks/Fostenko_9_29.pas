const n=1;
var A: array [1..n, 1..n] of real;
i,g,imin,gmin,gmax,imax: integer;
product: real;
begin
    read(A[1,1]);
    imin:=1;
    imax:=1;
    gmin:=1;
    gmax:=1;
    for g:=2 to n do begin
        read(A[1,g]);
        if A[1,g]<A[1,gmin] then gmin:=g;
    end;
    for i:=2 to n do
        for g:=1 to n do begin
            read(A[i,g]);
            if A[i,g]<A[imin,gmin] then begin
                imin:=i;
                gmin:=g;
            end
            else if A[i,g]>A[imax,gmax] then begin
                imax:=i;
                gmax:=g;
            end
        end;
    product:=0;
    for i:=1 to n do
        product:=product+A[imax,i]*A[i,gmin];
    writeln(product);
end.