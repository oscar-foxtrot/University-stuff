const n=1;
var i, min: integer;
arr: array [1..n] of integer;
begin
    read(arr[1]);
    min:=1;
    for i:=2 to n do begin
        read(arr[i]);
        if arr[i]<arr[min] then min:=i
    end;
    for i:=1 to n do if arr[i]<>arr[min] then write(arr[i],' ');
end.
