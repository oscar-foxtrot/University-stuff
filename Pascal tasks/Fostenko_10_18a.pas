const n=50;
m=40;
var wordseq: array [1..n] of string[m];
counter1, counter2: byte;
ch: char;
i,g:byte;
begin
    counter1:=1;
    counter2:=0;
    repeat
        read(ch);
        if (ch=' ') then begin
            setlength(wordseq[counter1], counter2);
            while ch=' ' do read(ch);
            inc(counter1);
            wordseq[counter1][1]:=ch;
            counter2:=1;
            continue;
        end;
        inc(counter2);
        wordseq[counter1][counter2]:=ch;
    until ch='.';
    setlength(wordseq[counter1], counter2-1);
    for i:=2 to counter1 do if not((length(wordseq[i-1])=length(wordseq[counter1])) 
        and (wordseq[i-1]=wordseq[counter1])) 
        then begin
            ch:=wordseq[i-1][1];
            for g:=2 to length(wordseq[i-1]) do wordseq[i-1][g-1]:=wordseq[i-1][g];
            wordseq[i-1][length(wordseq[i-1])]:=ch;
            write(wordseq[i-1],' ');
        end;
end.
