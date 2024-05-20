var Vn,Ve,Pwg,Pl,V,Pdg,Bch,Pb,C2:real;
VnT,VeT,LoadT,EmptyBST,EmptyPB,EmptyBCH,EmptyPDG:text;
Bst:shortint;
i:integer;
procedure windP (m:real); //m - скор. ветра
begin
if (m>0) and (m<3.5) then Pwg:=0 else
 if (m>3.5) and (m<4) then Pwg:=(m-3.5)*6 else
  if (m>4) and (m<4.5) then Pwg:=3+(m-4)*14 else
   if (m>4.5) and (m<5) then Pwg:=10+(m-4.5)*16 else
    if (m>5) and (m<6) then Pwg:=18+(m-5)*18 else
     if (m>6) and (m<7) then Pwg:=36+(m-6)*22 else
      if (m>7) and (m<8) then Pwg:=58+(m-7)*40 else
       if (m>8)and (m<8.5) then Pwg:=98+(m-8)*42 else
        if (m>8.5) and (m<9) then Pwg:=119+(m-8.5)*44 else
         if (m>9) and (m<9.5) then Pwg:=141+(m-9)*46 else
          if (m>9.5) and (m<10) then Pwg:=164+(m-9.5)*50 else
           if (m>10) and (m<10.5) then Pwg:=189+(m-10)*52 else
            if (m>10.5) and (m<11) then Pwg:=215+(m-10.5)*56 else
             if (m>11) and (m<11.5) then Pwg:=243+(m-11)*38 else
              if (m>11.5) and (m<12) then Pwg:=262+(m-11.5)*26 else
               if (m>12) and (m<20) then Pwg:=275;
end;

begin
assign (VnT, 'D:\ФостенкоОА_Королёв\Текстовые файлы с данными (для программ)\wind-north-direction.txt');
assign (VeT, 'D:\ФостенкоОА_Королёв\Текстовые файлы с данными (для программ)\wind-east-direction.txt');
assign (LoadT, 'D:\ФостенкоОА_Королёв\Текстовые файлы с данными (для программ)\load.txt');
reset (VnT);
reset (VeT);
reset (LoadT);
Bch:=0;
C2:=0;

for i:=1 to 8760 do begin
readln (VnT, Vn);
readln (VeT, Ve);
V:=sqrt(Vn*Vn+Ve*Ve);
windP (V);
readln (LoadT, Pl); // К этому моменту известны: Pwg, Pl.

if (Pwg>Pl) and (Bch<250) then begin
  Bst:=1;
  Pdg:=0;
  if (Bch+(Pwg-Pl)*0.95)<=250 then Pb:=Pwg-Pl else Pb:=(250-Bch)/0.95;
  Bch:=Bch+Pb*0.95;
  end
  else
if (Pwg=Pl) or ((Pl<=Pwg) and (Bch=250)) or ((Pl>=Pwg) and (Bch=0)) then begin
  Bst:=0;
  Pb:=0;
  if (Pwg=Pl) or ((Pl<Pwg) and (Bch=250)) then Pdg:=0 else Pdg:=Pl-Pwg;
  end
else begin // ((Bch>0) and (Pl>Pwg)) or ((Bch=250) and (Pl>Pwg))
  Bst:=-1;
  if (Bch-(Pl-Pwg))>=0 then begin 
  Pb:=(Pl-Pwg); Bch:=Bch-Pb; 
  end
  else begin {батарея разрядится насколько это возможно + активируется дизельный генератор}
  Pb:=Bch; Pdg:=Pl-Pwg-Pb; Bch:=0;
  end
  end;

C2:=C2+12.5+Pdg*0.2;
end;
Write (c2);
close (VnT); close (VeT); close (LoadT);
end. 