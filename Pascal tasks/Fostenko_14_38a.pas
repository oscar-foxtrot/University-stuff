type vowels = set of 'a'..'u';
const V = ['a','e','i','o','u'];
var S, L: vowels;
c: char;
twocommas: boolean;
begin
    S:=V;
    while c<>'.' do begin
        L:=[];
        read(c);
        if (c=',') or (c='.')
            then begin write('Error'); halt end;
        while (c<>'.') and (c<>',') do begin
            if (c<'a') or (c>'z')
                then begin write('Error'); halt end;
            if c in V then L:=L+[c];
            read(c);
        end;
        S:=S*L;
    end;
    for c:='a' to 'u' do if c in S then write(c);
end.
