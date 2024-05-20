var c: char;
x : integer;
sum: longint;
ispositive: boolean;

begin
    x:=0;
    sum:=0;
    ispositive:=true;
    read(c);
    while (c<>'.') do begin
        if (c<>'+') and (c<>'-') then
            x:=x*10+ord(c)-ord('0')
            else begin
                if ispositive then sum:=sum+x else sum:=sum-x;
                x:=0;
                if c='+' then ispositive:=true else ispositive:=false;
            end;
        read (c);
    end;
    if ispositive then sum:=sum+x else sum:=sum-x;
    writeln(sum);

end.
