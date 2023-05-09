program var a: int[10], b, i, tmp: int[1], f: bool;
begin
	read(b[0]);
	i[0] := 0;
	while i[0] < b[0] do
	begin
		read(a[i[0]]);
		i[0] := i[0] + 1
	end;
	{bubble sort}
	f := true;
	while f do
	begin
		f := false;
		i[0] := 0;
		while i[0] < b[0] - 1 do
		begin
			if a[i[0]] > a[i[0] + 1] then
			begin
				tmp[0] := a[i[0]];
				a[i[0]] := a[i[0] + 1];
				a[i[0] + 1] := tmp[0];
				f := true
			end
			else
				f := f;
			i[0] := i[0] + 1
		end
	end;
	i[0] := 0;
	while i[0] < b[0] do
	begin
		write(a[i[0]]);
		i[0] := i[0] + 1
	end
end @
