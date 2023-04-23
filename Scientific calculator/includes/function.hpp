#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>

#include "variable.hpp"
#include "anynum.hpp"

class Function
{
    struct Functree;
public:
    Function();
    Function(int arg);
    Function(double arg);
    Function(const Function &other);
    Function(const Variable &arg);
    Function operator=(const Function &other);
    Function operator()(const Function &f_x) const;
    Function(const Anynum &arg);
    Anynum operator()(Anynum x) const;
    Anynum operator()(int x) const;
    Anynum operator()(double x) const;
    friend std::ostream &operator<<(std::ostream &os, const Functree &functree);
    friend Function operator+(const Function &one, const Function &other);
    friend Function operator-(const Function &one, const Function &other);
    friend Function operator*(const Function &one, const Function &other);
    friend std::ostream &operator<<(std::ostream &os, const Function &func);
    friend Function cos(const Function &arg);
    friend Function sin(const Function &arg);
    friend Function exp(const Function &arg);
    friend Function asin(const Function &arg);
    friend Function log(const Function &arg);

private:
    struct Functree
    {
        Functree();
        ~Functree(); // Destroy the tree (free memo)
        Functree *get_tree() const;
        void replace_var_nodes(const Function &x);
        void check_op_and_print(bool parneeded, bool paroverall) const;
        Anynum operator()(Anynum x) const; // calculate the value
        Functree *right = nullptr, *left = nullptr;
        std::string value;
        Anynum numvalue;
        bool isnum;
        bool isvar;
        bool iselemfunc;
    } *ftree = nullptr;
    Variable arg;

    Functree *get_tree() const; // Functions for internal purposes
    Function perform_operation(const Function &other) const;
    Function create_elemf_node(std::string functype) const;
};

std::ostream &operator<<(std::ostream &os, const Function::Functree &functree);
Function operator+(const Function &one, const Function &other);
Function operator-(const Function &one, const Function &other);
Function operator*(const Function &one, const Function &other);
std::ostream &operator<<(std::ostream &os, const Function &func);
Function cos(const Function &arg);
Function sin(const Function &arg);
Function exp(const Function &arg);
Function asin(const Function &arg);
Function log(const Function &arg);

#endif
