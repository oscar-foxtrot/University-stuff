procedure Lines(var F,G:text);
var i: integer;
c: char;
begin
    reset(F); rewrite(G);
    i:=1;
    while not eof(F) do begin
        write(G,i div 1000,i div 100 mod 10,i div 10 mod 10, i mod 10,' ');
        inc(i);
        while not eoln(F) do begin
            read(F,c);
            write(G,c);
        end;
        readln(F);
        writeln(G);
    end;
    close(F); close(G);
end;