type Tstr1=string[10]; Tstr2=string[12]; Tsex=(M,F);
Tstud=record
    name: record s_name:Tstr2; f_name:Tstr1 end;
    sex:Tsex;
    marks:array[1..5] of 2..5;
end;
Tfile=file of Tstud;

var S: Tfile;
D: text;
st: Tstud;
mks: record
    avmarks: array [0..29] of real;
    alreadyin: array [0..29] of boolean;
end;
i,g,k,max:byte;

begin
    assign(S,'1.std'); assign(D,'2.txt');
    reset(S); rewrite(D);
    if FileSize(S)>30 then write(D,'Количество записей больше максимально допустимого')
    else if FileSize(S)>=1 then begin
        for i:=0 to FileSize(S)-1 do begin
            read(S,st);
            mks.avmarks[i]:=(st.marks[1]+st.marks[2]+st.marks[3]+st.marks[4]+st.marks[5])/5;
            mks.alreadyin[i]:=false;
        end;
        for i:=0 to FileSize(S)-1 do begin
            for k:=0 to FileSize(S)-1 do if not(mks.alreadyin[k]) then begin max:=k; break end;
            for g:=k+1 to FileSize(S)-1 do if not(mks.alreadyin[g]) then if (mks.avmarks[g]>mks.avmarks[max]) then max:=g;
            mks.alreadyin[max]:=true;
            seek(S,max);
            read(S,st);
            write(D,st.name.s_name,' ',st.name.f_name,' ',mks.avmarks[max]:0:1);
            writeln(D);
        end;
    end;
    close(S); close(D);
end.
