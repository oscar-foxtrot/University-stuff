type TTree = ^node;
node = record
    data: char;
    left,right: TTree;
end;

TStack = ^elem;
elem = record
    next: TStack;
    data: char;
end;

//1. Present the formula as a binary tree
//(Use the Postfix presentation?) ALL DONE
procedure initS(var st: TStack);
begin
    st:=nil;
end;

procedure pushS(c: char; var st: TStack);
var s: TStack;
begin
    new(s);
    s^.next:=st;
    s^.data:=c;
    st:=s;
end;

function popS(var st: TStack): char;
var s: TStack;
begin
    popS:=st^.data;
    s:=st^.next;
    dispose(st);
    st:=s;
end;

const args = ['0'..'9','X'];
procedure ReadFormula(var stmain: TStack);
procedure Err();
begin
    write('Error');
    halt;
end;
var flagoppar, flagclpar, flagnum, flagopw: boolean;
var sthelper: TStack;
frml: AnsiString;
parentheses, i: integer;
begin
    parentheses:=0;
    read(frml);
    flagoppar:=false; flagclpar:=false; flagopw:=false; flagnum:=false;
    for i:=1 to length(frml) do begin       //INPUT CHECK (USE STACK NOT ANSISTRING) !!!!!!
        if frml[i]='(' then begin
            inc(parentheses);
            if (flagclpar) or (flagnum) then Err()
                else begin flagoppar:=true; flagopw:=false end
        end
        else if frml[i]=')' then begin
            dec(parentheses);
            if ((parentheses<1) and (i<length(frml))) or (flagoppar)
                or (flagopw) then Err() else begin flagnum:=false; flagclpar:=true; flagopw:=false end
        end
        else if frml[i] in args then begin
            if (flagclpar) or (flagnum) then Err()
                else begin flagnum:=true; flagoppar:=false end
        end
        else if frml[i] in ['+','-','*'] then begin
            if (flagopw) or (flagoppar) then Err()
                else begin flagnum:=false; flagoppar:=false; flagopw:=true end;
        end else Err();
    end;
    if parentheses<>0 then Err();
    initS(sthelper);                        //STARTING TO PROCESS THE CORRECT STRING
    for i:=1 to length(frml) do begin
        if frml[i]=')' then begin
            pushS(popS(sthelper),stmain);   //Extract the binary op. from the Hstack -> place it in the Mstack
        end
        else if frml[i] in args then pushS(frml[i],stmain)
        else if frml[i] in ['+','-','*'] then pushS(frml[i],sthelper);
    end;
end;

//Extract Args from the Stack and put 'em into a Tree form
procedure ConvertIntoTree(var st: Tstack; var tree: TTree);
begin
    tree^.data:=popS(st);
    if tree^.data in ['*','+','-'] then begin
        ConvertIntoTree(st, tree^.right);
        ConvertIntoTree(st, tree^.left);
    end;
end;

var postf: TStack;
var tree: TTree;
begin
    ReadFormula(postf);
    //ConvertIntoTree(postf, tree);
    while postf<>nil do write(popS(postf)); 
end.