const n=50;
m=40+1;
var i,g,mcount,ncount: byte;
s: array[1..n] of string[m];

begin
    ncount:=1;
    mcount:=0;
    while true do begin
        inc(mcount);
        read(s[ncount][mcount]);
        if (s[ncount][mcount]=' ') then begin
            setlength(s[ncount],mcount-1);
            inc(ncount);
            repeat read(s[ncount][1]) until s[ncount][1]<>' ';
            mcount:=1;
        end
        else if (s[ncount][mcount]='.') then begin
            setlength(s[ncount],mcount-1);
            break;
        end;
    end;

    for i:=1 to n-1 do begin
        if s[i]=s[ncount] then continue
            else for g:=2 to length(s[i]) do if s[i][1]=s[i][g] then begin
                write(s[i],' ');
                break
            end;
    end;
end.

