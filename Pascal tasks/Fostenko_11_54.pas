function GCD(M,N: longint): longint;
begin
    if M=N then GCD:=M else
        if M>N then GCD:=GCD(M-N, N)
            else GCD:=GCD(M, N-M);
end;

const n=4;
var nums: array [1..n] of longint;
i: byte;
gcm: longint;
begin
    for i:=1 to n do begin
        read(nums[i]);
        if nums[i]<=0 then begin
            write('Error');
            halt;
        end;
    end;
    gcm:=nums[1];
    for i:=2 to 4 do gcm:=gcm*nums[i] div GCD(gcm, nums[i]);
    write(gcm);
end.