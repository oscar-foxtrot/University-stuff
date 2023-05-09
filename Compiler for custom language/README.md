P → program D1; B@  
D1 → var D {, D}  
D → I {, I}: [ int[N] | bool ]  
B → begin S {; S} end  
S → I[E] := E | I := E | if E then S else S | while E do S | B | read(I) | read(I[E]) | write(E)  
E → E1 [ == | < | > | != | <= | >= ] E1 | E1  
E1 → T {[ + | - | or ] T}  
T → F {[ * | / | and ] F}  
F → I[E] | I | N | L | not F | (E)  
L → true | false  
I → C | IC | IR  
N → R | NR  
C → a | b | ... | z | A | B | ... | Z  
R → 0 | 1 | 2 | ... | 9  

Above is the language description. Let's call it M-language (M-lang)  
Note: In the description above {<character>} means iterations - "choosing" the path multiple times.  
Note: In the description above [<symbol1> | <symbol2>] means "choice required". Exactly one of the values should be "picked"  
M-lang features int arrays and bool values and syntax similar to that of Pascal  
That is enough for performing key sorting, for example  
Supported integer numbers are of the same size as in C++, that is 4 bytes.  
Compilation is performed using recursive descent parser method. The language allows for it, as it is simple enough.  

##### main.cpp contains the whole interpreter    
##### Prog.ml features a possible program: a maximum of 10 ints are entered and then bubble-sorted. The result is then printed  
##### Use ./main.cpp file_name where file_name is the path of the file containing the program  
