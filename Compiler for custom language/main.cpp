#include <iostream>
#include <list>
#include <cstring>
#include <fstream>
#include <exception>
#include <stack>
#include <vector>

enum type_of_lex
{
    LEX_NULL,
    LEX_AND,
    LEX_BEGIN,
    LEX_BOOL,
    LEX_DO,
    LEX_ELSE,
    LEX_END,
    LEX_IF,
    LEX_FALSE, // 8
    LEX_INT,
    LEX_NOT, // 10
    LEX_OR,
    LEX_PROGRAM,
    LEX_READ,
    LEX_THEN,
    LEX_TRUE,
    LEX_VAR,
    LEX_WHILE,
    LEX_WRITE,
    LEX_FIN, // 19

    LEX_SEMICOLON,
    LEX_COMMA,
    LEX_COLON,
    LEX_ASSIGN, // 23
    LEX_LPAREN,
    LEX_RPAREN,
    LEX_EQ,
    LEX_LSS,
    LEX_GTR, // 28
    LEX_PLUS,
    LEX_MINUS,
    LEX_TIMES,
    LEX_SLASH,
    LEX_LEQ,
    LEX_NEQ,
    LEX_GEQ,
    LEX_NUM, // 36
    LEX_ID, // 37
    LEX_LBRAC,
    LEX_RBRAC,
    LEX_IDINDEXED, // indexed id

    POLIZ_LABEL, // 41
    POLIZ_ADDRESS, // 42
    POLIZ_GO, // 43
    POLIZ_FGO, // 44
    POLIZ_ADDRINDEXED // 45 Indexed address
};


class Lex
{
    type_of_lex t_lex;
    int v_lex;
public:
    Lex(type_of_lex t = LEX_NULL, int v = 0): t_lex(t), v_lex(v) {}
    type_of_lex get_type() const {return t_lex;}
    int get_value() const {return v_lex;}
    friend std::ostream& operator<<(std::ostream &s, Lex l)
    {
        s << '(' << l.t_lex << ',' << l.v_lex << ");";
        return s;
    }
};

// What do we do about arrays:
// We can access any element of the array, whether it contains garbage
// (uninitialized) or it was assigned something
class Id
{
    std::string name; // identifier name
    bool declared; // is identifier declared?
    bool assigned; // is it assigned something?
    type_of_lex type; // type of identifier
    int value; // value of the variable
    int size;
    int *intarr; // value if array of ints
    bool isarr;
public:
    Id()
    {
        declared = false;
        assigned = false;
        intarr = nullptr;
        isarr = false;
        size = 0; // for arrays
    }
    ~Id()
    {
        if (intarr)
            delete[] intarr;
    }
    std::string get_name() const {return name;}
    void set_name(const std::string &n) {name = n;}
    bool get_declared() const {return declared;}
    void set_declared() {declared = true;}
    type_of_lex get_type() const {return type;}
    void set_type(type_of_lex t) {type = t;}
    bool get_assigned() const {return assigned;}
    void set_assigned() {assigned = true;}
    int get_value() const {return value;}
    void set_value(int v) {value = v;}
    bool get_isarr() const {return isarr;}
    void set_isarr(int v) {isarr = v;}
    int get_size() const {return size;}
    void set_size(int v) 
    {
        size = v;
        intarr = new int[size];
    }
    int get_int(int pos) 
    {
        if (pos < size)
            return intarr[pos];
        else
            throw std::out_of_range("Index out of bounds");
    }
    void set_int(int pos, int value)
    {
        if (pos < size)
            intarr[pos] = value;
        else
            throw std::out_of_range("Index out of bounds");
    }
};


class Tid // Table of identifiers
{
    std::vector<Id> ids;
public:
    Id &operator[](int k) {return ids[k];}
    int put(const std::string &buf);
};

int Tid::put(const std::string &buf) // returns the position of the new elem in the table
{
    for (int j = 0; j < ids.size(); ++j)
        if (buf == ids[j].get_name())
            return j;
    ids.push_back(Id());
    ids[ids.size() - 1].set_name(buf);
    return ids.size() - 1;
}

/* TW — keywords table
TD — delimeters (separators and other spec. symbols) table
TID — identifiers table; */

class Scanner
{
    enum state {H, IDENT, NUMB, COM, ALE, DELIM, NEQ};
    static const std::string tw[];
    static type_of_lex words[];
    static const std::string td[];
    static type_of_lex dlms[];
    state CS; // current state
    std::fstream fs;
    char c;
    char buf[256]; // Buffer size (max identifier size (or number size))
    int buf_top;
    int curline; // for tracking the line in which the error occured
    void clear()
    {
        buf_top = 0;
        for (int j = 0; j < 80; ++j)
            buf[j] = '\0';
    }
    void add() {buf[buf_top++] = c;}
    int look(const std::string &buf, const std::string *list) const // The first and last elements of the "list" must be special
    {
        int i = 1;
        while (list[i] != "")
        {
            if (buf == list[i])
                return i;
            ++i;
        }
        return 0; // Not found
    }
    bool gc() /*c = fgetc(fp);*/
    {
        c = fs.get();
        return !fs.fail(); // true if successful, false on failure
    }

public:
    int get_curline() {return curline;} // for tracking the line in which the error occured
    Lex get_lex();
    Scanner(const std::string &program)
    {
        fs.open(program, std::ios_base::in); // open for reading
        if (fs.fail())
            throw std::runtime_error("Can't open the file \"" + program + "\" for reading");
        curline = 1;
        CS = H;
        clear();
        gc();
    }
    ~Scanner() {fs.close();}
};

/* TW[], words[] and TD[], dlms[] are organized in such a way that 
the lexeme tw[i] has type words[i] 
and the lexeme td[j] has type dlms[j] */

const std::string Scanner::tw[] =
{
    "\0", // 0 unused
    "and", // 1
    "begin", // 2
    "bool", // 3
    "do", // 4
    "else", // 5
    "end", // 6
    "if", // 7
    "false", // 8
    "int", // 9
    "not", // 10
    "or", // 11
    "program", // 12
    "read", // 13
    "then", // 14
    "true", // 15
    "var", // 16
    "while", // 17
    "write", // 18
    "\0" // 19
};

const std::string Scanner::td[] =
{
    "\0", // 0 unused
    "@", // 1
    ";", // 2
    ",", // 3
    ":", // 4
    ":=", // 5
    "(", // 6
    ")", // 7
    "=", // 8
    "<", // 9
    ">", // 10
    "+", // 11
    "-", // 12
    "*", // 13
    "/", // 14
    "<=", // 15
    "!=", // 16
    ">=", // 17
    "[", // 18
    "]", // 19
    "\0" // 20
};

Tid tid;
type_of_lex Scanner::words[] = {
    LEX_NULL,
    LEX_AND,
    LEX_BEGIN,
    LEX_BOOL,
    LEX_DO,
    LEX_ELSE,
    LEX_END,
    LEX_IF,
    LEX_FALSE,
    LEX_INT,
    LEX_NOT,
    LEX_OR,
    LEX_PROGRAM,
    LEX_READ,
    LEX_THEN,
    LEX_TRUE,
    LEX_VAR,
    LEX_WHILE,
    LEX_WRITE,
    LEX_NULL
};

type_of_lex Scanner::dlms[] = {
    LEX_NULL,
    LEX_FIN,
    LEX_SEMICOLON,
    LEX_COMMA,
    LEX_COLON,
    LEX_ASSIGN,
    LEX_LPAREN,
    LEX_RPAREN,
    LEX_EQ,
    LEX_LSS,
    LEX_GTR,
    LEX_PLUS,
    LEX_MINUS,
    LEX_TIMES,
    LEX_SLASH,
    LEX_LEQ,
    LEX_NEQ,
    LEX_GEQ,
    LEX_LBRAC,
    LEX_RBRAC,
    LEX_NULL
}; 

// The states are {H, IDENT, NUMB, COM, ALE, DELIM, NEQ}
Lex Scanner::get_lex()
{
    int d, j;
    CS = H;
    do
    {
        switch(CS)
        {
        case H: // starting state
            if (c == ' ' || c == '\n' || c== '\r' || c == '\t')
            {
                if (c == '\n')
                {
                    ++curline;
                }
                gc();
            }
            else if (isalpha(c))
            {
                clear();
                add();
                gc();
                CS = IDENT;
            }
            else if (isdigit(c))
            {
                d = c - '0';
                gc();
                CS = NUMB;
            }
            else if (c == '{')
            {
                gc();
                CS = COM;
            }
            else if (c == ':' || c == '<' || c == '>')
            {
                clear();
                add();
                gc();
                CS = ALE;
            }
            else if (c == '@')
            {
                return Lex(LEX_FIN);
            }
            else if (c == '!')
            {
                clear();
                add();
                gc();
                CS = NEQ;
            }
            else
            {
                CS = DELIM; // // // // //
            }
            break;
        case IDENT: // identifier
            if (isalpha(c) || isdigit(c))
            {
                add();
                gc();
            }
            else 
                if (j = look(buf, tw)) // determine whether the lex is a keyword or not
                    return Lex(words[j], j);
                else
                {
                    j = tid.put(buf);
                    return Lex(LEX_ID, j);
                }
            break;
        case NUMB: // number
            if (isdigit(c))
            {
                d = d * 10 + (c - '0');
                gc();
            }
            else
                return Lex(LEX_NUM, d);
            break;
        case COM: // commentary
            if (c == '}')
            {
                gc();
                CS = H;
            }
            else if (c == '@' || c == '{')
                throw c; // unexpected characters encountered
            else
                gc();
            break;
        case ALE: // proceeding to read that ONE delimiter
            if (c == '=') // the second symbol in a delimiter can only be a '='
            {
                add();
                gc();
                j = look(buf, td);
                return Lex(dlms[j], j);
            }
            else
            {
                j = look(buf, td);
                return Lex(dlms[j], j);
            }
            break;
        case NEQ: // proceeding to read "not equal" spec. sequence (!=)
            if (c == '=')
            {
                add();
                gc();
                j = look(buf, td);
                return Lex(LEX_NEQ, j);
            }
            else
                throw '!';
            break;
        case DELIM:
            clear();
            add();
            if (j = look(buf, td))
            {
                gc();
                return Lex(dlms[j], j);
            }
            else
                throw c; // unexpected character encountered while "consuming" a delimeter
            break;
        } // end switch
    }
    while(true);
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
// Next up: syntax (including Polish notation) //
/////////////////////////////////////////////////
/////////////////////////////////////////////////

class Poliz
{
    std::vector<Lex> lexs; // vector
public:
    void put_lex(Lex l) {lexs.push_back(l);}
    void put_lex(Lex l, int place) {lexs[place] = l;}
    void blank() {lexs.push_back(LEX_NULL);} // reserving space (for labels) (insert blank space)
    int get_free() {return lexs.size();}
    Lex &operator[](int index)
    {
        if (index >= lexs.size())
            throw std::out_of_range("Inverse notation error. Index out of bounds");
        else
            return lexs[index];
    };
    void print()
    {
        for (int i = 0; i < lexs.size(); ++i)
            std::cout << i << ": " << lexs[i] << std::endl;
    };
};

class Parser
{
    Lex curr_lex; // current lexeme
    type_of_lex c_type;
    int c_val;
    Scanner scan;
    std::stack<int> st_int;
    std::stack<type_of_lex> st_lex;
    void P();
    void D1();
    void D();
    void B();
    void S();
    void E();
    void E1();
    void T();
    void F();
    void dec(type_of_lex type, bool isarr = false, int size = 0); // "semantic actions" (checking for repeated declaration)
    //void check_id();
    void check_op();
    void check_not();
    void eq_type();
    void eq_bool();
    void check_id_in_read();
    void gl() // get the next lexeme
    {
        curr_lex = scan.get_lex();
        c_type = curr_lex.get_type();
        c_val = curr_lex.get_value();
    }

public:
    Poliz prog; // Internal representation of the program
    Parser(const std::string &program): scan(program) {}
    void analyze(); // analyzer
};

void Parser::analyze()
{
    try
    {
        gl();
        P();
    }
    catch(...)
    {
        std::cout << "Compilation error: line " << scan.get_curline() << " (unexpected lexeme)" << std::endl;
        throw;
    }
    //prog.print();
}

// The following procedures are completely in line with the M-lang description

void Parser::P()
{
    if (c_type == LEX_PROGRAM)
        gl();
    else
        throw curr_lex;
    D1();
    if (c_type == LEX_SEMICOLON)
        gl();
    else
        throw curr_lex;
    B();
    if (c_type != LEX_FIN)
        throw curr_lex;
}

void Parser::D1() 
{
    if (c_type == LEX_VAR)
    {
        gl(); 
        D();
        while (c_type == LEX_COMMA)
        { 
            gl();
            D();
        }
    }
    else
        throw curr_lex;
}

void Parser::D() 
{
    while (!st_int.empty())
        st_int.pop();
    if (c_type != LEX_ID)
        throw curr_lex;
    else 
    {
        st_int.push(c_val); // c_val is the number of identifier in tid (id table)
        gl();
        while (c_type == LEX_COMMA)
        {
            gl();
            if (c_type != LEX_ID)
                throw curr_lex;
            else
            {
                st_int.push(c_val); 
                gl();
            }
        }
        if (c_type != LEX_COLON)
            throw curr_lex;
        else 
        {
            gl();
            if (c_type == LEX_INT) // int[<number>]
            {
                gl();
                if (c_type == LEX_LBRAC)
                    gl();
                else
                    throw curr_lex;
                if (c_type == LEX_NUM)
                {
                    dec(LEX_INT, true, c_val); // declare an array. c_val is the value of number underlying the LEX_NUM
                    gl();
                }
                else
                    throw curr_lex;   
                if (c_type == LEX_RBRAC)
                    gl();
                else
                    throw curr_lex;
            }
            else if (c_type == LEX_BOOL)
            {
                dec(LEX_BOOL);
                gl();
            }
            else
                throw curr_lex;
        }
    }
}

void Parser::B()
{
    if (c_type == LEX_BEGIN)
    {
        gl();
        S();
        while (c_type == LEX_SEMICOLON)
        {
            gl();
            S();
        }
        if (c_type == LEX_END)
            gl();
        else
            throw curr_lex;
    }
    else
        throw curr_lex;
}

void Parser::S()
{
    int pl0, pl1, pl2, pl3;
    if (c_type == LEX_IF)
    {
        gl();
        E();
        eq_bool(); // is the expression of type boolean?
        pl2 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        if (c_type == LEX_THEN)
        {
            gl();
            S();
            pl3 = prog.get_free();
            prog.blank();
            prog.put_lex(Lex(POLIZ_GO));
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl2);
            if (c_type == LEX_ELSE)
            {
                gl();
                S();
                prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl3);
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    } // end if
    else if (c_type == LEX_WHILE)
    {
        pl0 = prog.get_free();
        gl();
        E();
        eq_bool();
        pl1 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        if (c_type == LEX_DO)
        {
            gl();
            S();
            prog.put_lex(Lex(POLIZ_LABEL, pl0));
            prog.put_lex(Lex(POLIZ_GO));
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1);
        }
        else
            throw curr_lex;
    } //end while
    else if (c_type == LEX_READ)
    {
        gl();
        if (c_type == LEX_LPAREN)
        {
            gl();
            if (c_type == LEX_ID)
            {
                check_id_in_read();
                Lex old_lex = Lex(POLIZ_ADDRESS, c_val);
                gl();
                if (c_type == LEX_LBRAC) // ADDED ADDED ADDED
                {
                    gl();
                    E();
                    type_of_lex curtype = st_lex.top();
                    st_lex.pop();
                    if (curtype != LEX_INT)
                        throw curr_lex;
                    if (c_type == LEX_RBRAC) // ADDED ADDED ADDED
                    {
                        gl();
                        prog.put_lex(Lex(POLIZ_ADDRINDEXED, old_lex.get_value())); // if address is indexed 
                    }
                    else
                        throw curr_lex;
                }
                else
                    prog.put_lex(old_lex); // if address not indexed 
            }
            else
                throw curr_lex;
            if (c_type == LEX_RPAREN)
            {
                gl();
                prog.put_lex(Lex(LEX_READ));
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    } //end read
    else if (c_type == LEX_WRITE)
    {
        gl();
        if (c_type == LEX_LPAREN)
        {
            gl();
            E();
            if (c_type == LEX_RPAREN)
            {
                gl();
                prog.put_lex(Lex(LEX_WRITE));
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    } //end write
    else if (c_type == LEX_ID)
    {
        if (!tid[c_val].get_declared()) // check_id()
            throw std::logic_error("Error. Trying to manipulate a variable that has not been declared"); //check_id();

        Lex old_lex = Lex(POLIZ_ADDRESS, c_val);
        gl();
        bool indexed = false;
        if (c_type == LEX_LBRAC)
        {
            indexed = true;
            gl();
            E();
            type_of_lex curtype = st_lex.top();
            st_lex.pop();
            if (curtype != LEX_INT) // reading index here
                throw curr_lex;
            if (c_type == LEX_RBRAC) // ADDED ADDED ADDED
            {
                gl();
                prog.put_lex(Lex(POLIZ_ADDRINDEXED, old_lex.get_value())); // if address is indexed
                st_lex.push(LEX_INT); // because we only have INT arrays
            }
            else
                throw curr_lex;
        }
        if (c_type == LEX_ASSIGN)
        {
            if (!indexed)
            {
                prog.put_lex(old_lex);
                st_lex.push(tid[old_lex.get_value()].get_type());
            }
            gl();
            E(); 
            eq_type(); // check the type
            prog.put_lex(Lex(LEX_ASSIGN));
        }
        else
            throw curr_lex;
    } //assign-end
    else B();
}

void Parser::E()
{
    E1();
    if (c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR ||
        c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ)
    {
        st_lex.push(c_type);
        gl();
        E1();
        check_op();
    }
}

void Parser::E1()
{
    T();
    while (c_type == LEX_PLUS || c_type == LEX_MINUS || c_type == LEX_OR)
    {
        st_lex.push(c_type);
        gl();
        T();
        check_op();
    }
}

void Parser::T()
{
    F();
    while (c_type == LEX_TIMES || c_type == LEX_SLASH || c_type == LEX_AND)
    {
        st_lex.push(c_type);
        gl();
        F();
        check_op();
    }
}

void Parser::F()
{
    if (c_type == LEX_ID)
    {
        if (!tid[c_val].get_declared()) // check_id()
            throw std::logic_error("Error. Trying to manipulate a variable that has not been declared");
        Lex old_lex = Lex(LEX_ID, c_val);
        gl();
        if (c_type == LEX_LBRAC)
        {
            gl();
            E();
            type_of_lex curtype = st_lex.top();
            st_lex.pop();
            if (curtype != LEX_INT) // reading index here
                throw curr_lex;
            if (c_type == LEX_RBRAC) // ADDED ADDED ADDED
            {
                prog.put_lex(Lex(LEX_IDINDEXED, old_lex.get_value())); // ADDED ADDED ADDED
                st_lex.push(LEX_INT);
                gl();
            }
            else
                throw curr_lex;
        }
        else
        {
            st_lex.push(tid[old_lex.get_value()].get_type()); // check_id()
            prog.put_lex(old_lex);
        }
    }
    else if (c_type == LEX_NUM)
    {
        st_lex.push(LEX_INT);
        prog.put_lex(curr_lex);
        gl();
    }
    else if (c_type == LEX_TRUE)
    {
        st_lex.push(LEX_BOOL);
        prog.put_lex(Lex(LEX_TRUE, 1));
        gl();
    }
    else if (c_type == LEX_FALSE)
    {
        st_lex.push(LEX_BOOL);
        prog.put_lex(Lex(LEX_FALSE, 0));
        gl();
    }
    else if (c_type == LEX_NOT)
    {
        gl();
        F();
        check_not();
    }
    else if (c_type == LEX_LPAREN)
    {
        gl();
        E();
        if (c_type == LEX_RPAREN)
            gl();
        else
            throw curr_lex;
    }
    else
        throw curr_lex;
}

void Parser::dec(type_of_lex type, bool isarr, int size)
{
    int i;
    while (!st_int.empty())
    {
        i = st_int.top();
        st_int.pop();
        if (tid[i].get_declared())
            throw std::logic_error("Error. Repeated declaration of a variable");
        else
        {
            tid[i].set_declared();
            tid[i].set_type(type);
            tid[i].set_isarr(isarr);
            tid[i].set_size(size);
        }
    }
}

void Parser::check_op()
{
    type_of_lex t1, t2, op, operation_type;
    t2 = st_lex.top();
    st_lex.pop();
    op = st_lex.top();
    st_lex.pop();
    t1 = st_lex.top();
    st_lex.pop();
    if (op == LEX_OR || op == LEX_AND)
        operation_type = LEX_BOOL; // type of operands acutally
    else // There are a lot of int operations
        operation_type = LEX_INT; // type of operands actually
    if (t1 == t2 && t1 == operation_type)
    {
        if (op == LEX_PLUS || op == LEX_MINUS
            || op == LEX_TIMES || op == LEX_SLASH)
            operation_type = LEX_INT;
        else
            operation_type = LEX_BOOL;
        st_lex.push(operation_type);
        prog.put_lex(Lex(op));
    }
    else
        throw std::logic_error("Error. Unsupported operation or operands are of different type");
}

void Parser::check_not()
{
    type_of_lex top = st_lex.top();
    st_lex.pop();
    if (top != LEX_BOOL)
        throw std::logic_error("Error. Trying to negate unsupported type");
    else
    {
        st_lex.push(LEX_BOOL);
    }
}

void Parser::eq_type()
{
    type_of_lex top0 = st_lex.top();
    st_lex.pop();
    type_of_lex top1 = st_lex.top();
    st_lex.pop();
    if (top0 != top1) 
        throw std::logic_error("Error. Trying to assign a variable an expression of a wrong type");
}

void Parser::eq_bool()
{
    type_of_lex top = st_lex.top();
    st_lex.pop();
    if (top != LEX_BOOL)
        throw std::logic_error("Error. Expression of type \"boolean\" expected");
}

void Parser::check_id_in_read()
{
    if (!tid[c_val].get_declared())
        throw std::logic_error("Error. Trying to manipulate a variable that has not been declared");
}

///////////////////////////////////////////
///////////////////////////////////////////
// Next up: Interpreting Polish notation //
///////////////////////////////////////////
///////////////////////////////////////////

class Executer
{
    Lex pc_el;
public:
    void execute(Poliz& prog);
};

struct Key // value-index pair
{
    int elems[2];
    Key(int arg0, int arg1 = -1) 
    {
        elems[0] = arg0; // number in tid 
        elems[1] = arg1; // index (if any)
    }
    operator int() {return elems[0];}
};

void Executer::execute(Poliz& prog) // add line where error occured?
{
    std::stack<Key> args; // instead of ints we may want use something different
    Key i(-1), j(-1);
    int k, index = 0, fin = prog.get_free();
    while(index < fin)
    {
        pc_el = prog[index];
        switch (pc_el.get_type())
        {
        case LEX_TRUE:
        case LEX_FALSE:
        case LEX_NUM:
        case POLIZ_ADDRESS:
        case POLIZ_LABEL:
            args.push(pc_el.get_value());
            break;
        case POLIZ_ADDRINDEXED: // ADDED ADDED ADDED Indexation
            i = args.top(); // index
            args.pop();
            args.push(Key(pc_el.get_value(), i));
            break;
        case LEX_IDINDEXED: // ADDED ADDED ADDED Indexation
            i = pc_el.get_value();
            if (tid[i].get_assigned() || tid[i].get_isarr()) // if array, then we don't care about garbage values being accessed
            {
                j = args.top(); // index
                args.pop();
                args.push(tid[i].get_int(j));
                break;
            }
            else
                throw std::runtime_error("Runtime error: accessing an uninitialized variable");
        case LEX_ID:
            i = pc_el.get_value();
            if (tid[i].get_assigned() || tid[i].get_isarr()) // if array, then we don't care about garbage values being accessed
            {
                args.push(tid[i].get_value());
                break;
            }
            else
                throw std::runtime_error("Runtime error: accessing an uninitialized variable");
        case LEX_NOT:
            i = args.top();
            args.pop();
            args.push(!i);
            break;
        case LEX_OR:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(j || i);
            break;
        case LEX_AND:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(j && i);
            break;
        case POLIZ_GO:
            i = args.top();
            args.pop();
            index = i - 1;
            break;
        case POLIZ_FGO:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            if (!j)
                index = i - 1;
            break;
        case LEX_WRITE:
            std::cout << (int)args.top() << std::endl;
            args.pop();
            break;
        case LEX_READ:
            i = args.top();
            args.pop();
            if (tid[i].get_type() == LEX_INT)
            {
                std::cout << "Input int value for ";
                std::cout << tid[i].get_name() << ", index " << i.elems[1] << ": ";
                std::cin >> k;
                if (std::cin.fail())
                    throw std::runtime_error("Error while reading");
                tid[i].set_int(i.elems[1], k);
            }
            else
            {
                std::string tmps;
                std::cout << "Input boolean value (true or false) for ";
                std::cout << tid[i].get_name() << ": ";
                std::cin >> tmps;
                if (std::cin.fail())
                    throw std::runtime_error("Error while reading");
                if (tmps == "true" || tmps == "1")
                    j = 1;
                else if (tmps == "false" || tmps == "0")
                    j = 0;
                else
                    throw std::runtime_error("Expected value of type boolean (true/false or 0/1). Got \"" + tmps + "\"");
                tid[i].set_value(j);
            }
            tid[i].set_assigned();
            break;
        case LEX_PLUS:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(i + j);
            break;
        case LEX_TIMES:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(i * j);
            break;
        case LEX_MINUS:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(j - i);
            break;
        case LEX_SLASH:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            if (!i)
            {
                args.push(j / i);
                break;
            }
            else 
                throw std::runtime_error("Division by zero");
        case LEX_EQ:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(i == j);
            break;
        case LEX_LSS:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(j < i);
            break;
        case LEX_GTR:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(j > i);
            break;
        case LEX_LEQ:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(j <= i);
            break;
        case LEX_GEQ:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(j >= i);
            break;
        case LEX_NEQ:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            args.push(j != i);
            break;
        case LEX_ASSIGN:
            i = args.top();
            args.pop();
            j = args.top();
            args.pop();
            if (j.elems[1] != -1)
            {
                tid[j].set_int(j.elems[1], i);
                tid[j].set_assigned();
            }
            else
            {
                tid[j].set_value(i);
                tid[j].set_assigned();
            }
            break;
        default:
            throw std::runtime_error("Something went wrong within the compiler");
        } // end of switch
        ++index;
    }; //end of while
}

class Interpreter
{ 
    Parser parser;
    Executer executer;
public:
    Interpreter(const std::string &program): parser(program) {};
    void interpret();
};

void Interpreter::interpret()
{
    parser.analyze();
    executer.execute(parser.prog);
}


int main(int argc, const char *argv[])
{
    Interpreter itpr(argv[1]);
    itpr.interpret();
    return 0;
}
