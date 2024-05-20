var c:char;
counter: integer;
k: integer;
begin
    counter:=0;
    read (c);
    while ((ord(c)<ord('0')) or (ord(c)>ord('9'))) and (c<>'.') do
    begin
        inc(counter);
        read(c);
    end;

    if (c='.') or (counter<1) then writeln('false')
        else begin
            k:=ord(c)-ord('0');
            read(c);
            if c<>'.' then writeln ('false')
                else if k=counter then writeln ('true')
                    else writeln ('false');
        end;
end.