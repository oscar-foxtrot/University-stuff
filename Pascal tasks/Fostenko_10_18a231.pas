const n=50;
m=40;
var wordseq: array [1..n] of string[m];
counter1, counter2: byte;
ch: char;
i,g:byte;
begin
    counter1:=1;
    counter2:=1;
    read(ch);
    while ch<>'.' do begin
        wordseq[counter1][counter2]:=ch;
        if ch=' ' then begin
            inc(counter1);
            while ch=' ' do read(ch);
            counter2:=1;
        end;
        read(ch);
    end;

    for i:=1 to n do write(wordseq[i][0]);
end.