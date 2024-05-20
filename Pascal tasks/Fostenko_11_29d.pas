procedure Negpos(var X: Tarray);
var a: Tarray;
i,nums: integer;
begin
    nums:=0;
    for i:=1 to n do
        if X[i]<0 then begin
            inc(nums);
            a[nums]:=X[i];
        end;
    for i:=1 to n do
        if X[i]>=0 then begin
            inc(nums);
            a[nums]:=X[i];
        end;
    for i:=1 to n do X[i]:=a[i];
end;
