procedure ass(var a: word); assembler;
asm
    MOV a, 5
end;
var
a: integer;
begin
    ass(a);
    writeln(a);
end.