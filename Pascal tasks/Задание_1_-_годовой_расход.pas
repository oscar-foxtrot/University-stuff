var Vn,Ve,WP,LP,V,C1,Ch:real;
VnT,VeT,LoadT:text;
i:integer;
procedure windP (m:real); //m - скор. ветра
begin
if (m>0) and (m<3.5) then WP:=0 else
 if (m>3.5) and (m<4) then WP:=(m-3.5)*6 else
  if (m>4) and (m<4.5) then WP:=3+(m-4)*14 else
   if (m>4.5) and (m<5) then WP:=10+(m-4.5)*16 else
    if (m>5) and (m<6) then WP:=18+(m-5)*18 else
     if (m>6) and (m<7) then WP:=36+(m-6)*22 else
      if (m>7) and (m<8) then WP:=58+(m-7)*40 else
       if (m>8)and (m<8.5) then WP:=98+(m-8)*42 else
        if (m>8.5) and (m<9) then WP:=119+(m-8.5)*44 else
         if (m>9) and (m<9.5) then WP:=141+(m-9)*46 else
          if (m>9.5) and (m<10) then WP:=164+(m-9.5)*50 else
           if (m>10) and (m<10.5) then WP:=189+(m-10)*52 else
            if (m>10.5) and (m<11) then WP:=215+(m-10.5)*56 else
             if (m>11) and (m<11.5) then WP:=243+(m-11)*38 else
              if (m>11.5) and (m<12) then WP:=262+(m-11.5)*26 else
               if (m>12) and (m<20) then WP:=275;
end;

begin
assign (VnT, 'D:\ФостенкоОА_Королёв\Текстовые файлы с данными (для программ)\wind-north-direction.txt');
assign (VeT, 'D:\ФостенкоОА_Королёв\Текстовые файлы с данными (для программ)\wind-east-direction.txt');
assign (LoadT, 'D:\ФостенкоОА_Королёв\Текстовые файлы с данными (для программ)\load.txt');
reset (VnT);
reset (VeT);
reset (LoadT);
C1:=0;

for i:=1 to 8760 do begin
readln (VnT, Vn);
readln (VeT, Ve);
V:=sqrt(Vn*Vn+Ve*Ve);
windP (V);
readln (LoadT, LP);
if LP<WP then Ch:=12.5 else Ch:=12.5+0.2*(LP-WP);
C1:=C1+Ch;
end;
close (VnT); close (VeT); close (LoadT);
write (C1);
end.