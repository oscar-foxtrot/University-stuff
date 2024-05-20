Program Variant5;
var s1:string;
t1,t2:text;
i,n,countst:byte;
begin
  
  assign (t1,'D:\NSP.txt'); assign (t2,'D:\NSV.txt');
  reset (t1); rewrite (t2);
  read (t1, s1);
  writeln (t2,'Исходная строка: ',s1); writeln;
  countst:=0;
 
  i:=1;
  while s1[i]<>' ' do i:=i+1;
  n:=i+1;
  for i:=n to length(s1) do if (s1[i]='*') then countst:=countst+1;
  i:=1;
  while s1[i]<>'.' do i:=i+1;
  n:=i+1;
  for i:=n to length(s1) do if (s1[i]=' ') then begin delete(s1,i,1); insert('.',s1,i); end;
   
    writeln (t2,'Измененная (новая) строка: ',s1); writeln;
    write (t2,'Количество "звездочек" после первого пробела - ',countst);
    
  
  close (t1); close (t2);
end.