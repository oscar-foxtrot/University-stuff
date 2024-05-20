const n=1;
var i, g, counter: integer;
arr: array [1..n] of integer;
begin
        counter:=0;
        for i:=1 to n do
        begin
                read(arr[i]);
                for g:=1 to i-1 do
                if arr[g]>arr[i] then inc(counter);
        end;
        writeln(counter)
end.