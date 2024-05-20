const Alpha = ['a'..'z','A'..'Z'];
var F: text;
symb,wrds: integer;
c: char;

begin
    assign(F,'1.txt');
    reset(F);
    symb:=0; wrds:=0;
    read(F,c);
    while true do begin
        while not(c in Alpha) do if not eof(F) then
            read(F,c) else break;
        while c in Alpha do begin
            inc(symb);
            read(F,c);
        end;
        if eof(F) then break;
        inc(wrds);
    end;
    close(F);
    if wrds=0 then write('0') else write(symb/wrds);
end.
