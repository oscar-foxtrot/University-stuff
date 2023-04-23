#ifndef VARIABLE_H
#define VARIABLE_H

class Variable
{
public:
    Variable();
    Variable(std::string val);
    friend std::ostream &operator<<(std::ostream &os, const Variable &var);
    std::string get_value() const;
private:
    std::string value;
};

#endif
