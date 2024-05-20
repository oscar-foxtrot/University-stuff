var Pwg,Pl,Pdg,Bch,Pb:real;
Bst:shortint;

begin
writeln ('Введите мощность нагрузки');
readln (Pl);
writeln ('Введите мощность ветрогенератора');               {INPUT}
readln (Pwg);
writeln ('Введите оставшийся заряд аккумуляторной батареи');
readln (Bch);

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
writeln ('Для оптимальной работы система должна иметь следующие параметры:');
writeln ('Мощность дизельного генератора: ',Pdg,' кВт');
writeln ('Статус накопителя энергии: ',Bst);            {OUTPUT}
writeln ('Мощность зарядки/разрядки: ',Pb,' кВт');

end.