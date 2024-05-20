{По пути 'D:\' (главный каталог диска D) создан текстовый файл, заполненный предварительно случайно сгенерированными ФИО 'NSP.txt'.
Содержимое:

Александрова Арина Александровна
Алексеев Александр Савельевич
Беляков Фёдор Максимович
Богданов Кирилл Тимофеевич
Ефремова Варвара Леонидовна
Коршунова Анна Сергеевна
Леонова Дарья Ильинична
Петрова Анна Вячеславовна
Смирнов Егор Григорьевич
Тихонов Марк Артёмович
Быков Александр
}
Program task07102020_2;
var f1:text;
i,c,m:byte;
s:string;
begin
  assign (f1,'D:\NSP.txt');
  reset (f1);
  c:=1;
  readln (f1, s);
  while length(s)>0 do begin
    c:=1;
    for i:=1 to 255 do begin
      if (s[i]=' ') and (c=1) then begin m:=i; c:=c+1; end 
      else if (s[i]=' ') and (c=2) then begin
      delete (s, m+2, i-m-2); insert ('.', s, m+2); break; end;
      end;

    delete (s, m+5, length(s)-m-4); insert ('.', s, m+5);
    
    writeln (s);
    readln (f1, s);
  end;
  close (f1);
end.

