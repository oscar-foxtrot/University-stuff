Program task07102020_1;
var s1,s2:string;
sarr:array [1..26] of byte; {A..Z = 26symb}
i:byte;

begin
  Write ('Введите строку 1: '); Readln (s1);
  Write ('Введите строку 2: '); Readln (s2);
  
  for i:=1 to length(s1) do begin
    if (s1[i]>='A') and (s1[i]<='Z') then begin
    if sarr[1+(ord(s1[i])-ord('A'))]=0 then sarr[1+(ord(s1[i])-ord('A'))]:=1; end else
    if (s1[i]>='a') and (s1[i]<='z') then begin
    if sarr[1+(ord(s1[i])-ord('a'))]=0 then sarr[1+(ord(s1[i])-ord('a'))]:=1; end; end;
  
  for i:=1 to length(s2) do begin
    if (s2[i]>='A') and (s2[i]<='Z') then begin
    if sarr[1+(ord(s2[i])-ord('A'))]=0 then sarr[1+(ord(s2[i])-ord('A'))]:=1; end else
    if (s2[i]>='a') and (s2[i]<='z') then begin
    if sarr[1+(ord(s2[i])-ord('a'))]=0 then sarr[1+(ord(s2[i])-ord('a'))]:=1; end; end;
  
  for i:=1 to 26 do
  if sarr[i]=1 then break;
 
 if i=26 then write ('В введенных строках не встречается ни одна буква латинского алфавита.') else
  write ('В введенных строках встречаются буквы латинского алфавита:');
  
  for i:=1 to 26 do if sarr[i]=1 then write (' ', chr(i+ord('a')-1));
  
end.
