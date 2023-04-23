#include <iostream>
#include <cmath>
#include <iomanip>
#include <exception>

#include "function.hpp"
#include "variable.hpp"
#include "anynum.hpp"

// Using only raw pointers, no STL smart ptrs///////////////////////////

Function::Functree::Functree() {}

Function::Function()
{
    ftree = new Functree;
    ftree->left = nullptr;
    ftree->right = nullptr;
    ftree->value = "0";
}

Function::Function(const Anynum &arg)
{
    ftree = new Functree;
    ftree->left = nullptr;
    ftree->right = nullptr;
    ftree->isvar = false;
    ftree->iselemfunc = false;
    ftree->isnum = true;
    ftree->numvalue = arg;
}

Function::Function(int arg): Function((Anynum)arg) {} // delegate

Function::Function(double arg): Function((Anynum)arg) {} // delegate

Function::Function(const Function &other)
{
    ftree = other.get_tree();
    arg = other.arg;
}

Function::Function(const Variable &arg)
{
    ftree = new Functree;
    ftree->left = nullptr;
    ftree->right = nullptr;
    ftree->isvar = true;
    ftree->isnum = false;
    ftree->iselemfunc = false;
    ftree->value = arg.get_value();
    this->arg = arg;
}

Function Function::operator=(const Function &other)
{
    delete ftree;
    ftree = other.get_tree();
    arg = other.arg;
    return *this;
}

Function Function::perform_operation(const Function &other) const
{
    if (arg.get_value() != other.arg.get_value() && !other.ftree->isnum && !ftree->isnum)  // MULTIPLICATION OF NUMS CAN BE ISNUM! RESOLVE! (combine flags?)
    {
        throw std::runtime_error("Incompatible variables. Make sure that the functions depend on only one variable\n");
    }
    Function res;
    res.ftree = new Functree;
    res.ftree->left = ftree->get_tree();
    res.ftree->right = other.ftree->get_tree();
    if (!other.ftree->isnum)
    {
        res.arg = other.arg;
    }
    else
    {
        res.arg = arg;
    }
    res.ftree->isvar = false;
    res.ftree->iselemfunc = false;
    res.ftree->isnum = false;
    return res;
}

Function operator+(const Function &one, const Function &other)
{ 
    Function res = one.perform_operation(other);
    res.ftree->value = " + ";
    return res;
}

Function operator-(const Function &one, const Function &other)
{
    Function res = one.perform_operation(other);
    res.ftree->value = " - ";
    return res;
}

Function operator*(const Function &one, const Function &other)
{
    Function res = one.perform_operation(other);
    res.ftree->value = " * ";
    return res;
}

void Function::Functree::replace_var_nodes(const Function &x) ///////////////////////////////////////
{
    if (right) // != nullptr
    {
        if (right->isvar)
        {
            delete right;
            right = x.ftree->get_tree();
        }
        else if (!right->isnum)
        {
            right->replace_var_nodes(x);
        }
    }
    if (left) // != nullptr
    {
        if (left->isvar)
        {
            delete left;
            left = x.ftree->get_tree();
        }
        else if (!left->isnum)
        {
            left->replace_var_nodes(x);
        }
    }
}

Function Function::operator()(const Function &x) const // Replace "var" nodes with corresponding "Function" nodes
{
    Function res;
    if (ftree->isvar)
    {
        res = x;
    }
    else 
    {
        res = *this;
        res.arg = x.arg;
        res.ftree->replace_var_nodes(x);
    }
    
    return res;
}

Anynum Function::operator()(Anynum x) const
{
    return (*ftree)(x);
}

Anynum Function::operator()(int x) const
{
    return (*ftree)(x);
}

Anynum Function::operator()(double x) const
{
    return (*ftree)(x);
}

Anynum Function::Functree::operator()(Anynum x) const
{
    if (!isvar && !iselemfunc && !isnum)
    {
        if (value == " * ")
        {
            return (*left)(x) * (*right)(x);
        }
        else if (value == " + ")
        {
            return (*left)(x) + (*right)(x);
        }
        else if (value == " - ")
        {
            return (*left)(x) - (*right)(x);
        }
    }
    else if (isvar)
    {
        return x;
    }
    else if (isnum)
    {
        return numvalue;
    }
    else
    {
        if (value == "sin")
        {
            return ((*right)(x)).sin(); // CHANGE CHANGE CHANGE
        }
        else if (value == "cos")
        {
            return ((*right)(x)).cos();
        }
        else if (value == "asin")
        {
            return ((*right)(x)).asin();
        }
        else if (value == "exp")
        {
            return ((*right)(x)).exp();
        }
        else if (value == "log")
        {
            return ((*right)(x)).log();
        }
    }
    return 0; // never happens, for silencing the warning
}

std::ostream &operator<<(std::ostream &os, const Function &func)
{
    return std::cout << *func.ftree;
}

void Function::Functree::check_op_and_print(bool parneeded, bool paroverall) const
{
    if (paroverall || (parneeded && !isvar && !isnum && value != " * " && !iselemfunc))
    {
        std::cout << "(" << *this << ")";
    }
    else
    {
        std::cout << *this;
    }
}

std::ostream &operator<<(std::ostream &os, const Function::Functree &functree)
{
    if (functree.value == " * " || functree.iselemfunc)
    {
        if (!functree.iselemfunc)
        {
            if (functree.left)
            {
                functree.left->check_op_and_print(true, false);
            }
            std::cout << functree.value;
            if (functree.right)
            {
                functree.right->check_op_and_print(true, false);
            }
        }
        else
        {
            if (functree.left)
            {
                functree.left->check_op_and_print(true, true);
            }
            std::cout << functree.value;
            if (functree.right)
            {
                functree.right->check_op_and_print(true, true);
            }
        }
    }
    else
    {
        if (functree.left)
        {
            functree.left->check_op_and_print(false, false);
        }
        if (!functree.isnum)
        {
            std::cout << functree.value;
        }
        else
        {
            if (compare(functree.numvalue, 0) == -1) //(functree.numvalue < 0)
            {
                std::cout << '(' << functree.numvalue << ')';
            }
            else
            {
                std::cout << functree.numvalue;
            }
        }
        if (functree.right)
        {
            functree.right->check_op_and_print(false, false);
        }
    }
    return std::cout;
}

Function::Functree::~Functree() // Functree destructor
{
    if (left != nullptr)
    {
        delete left;
    }
    if (right != nullptr)
    {
        delete right;
    }
}

Function::Functree *Function::Functree::get_tree() const
{
    Functree *res = new Functree;
    res->value = value;
    res->isvar = isvar;
    res->isnum = isnum;
    res->numvalue = numvalue;
    res->iselemfunc = iselemfunc;
    if (right != nullptr)
    {
        res->right = right->get_tree();
    }
    else
    {
        res->right = nullptr;
    }

    if (left != nullptr)
    {
        res->left = left->get_tree();
    }
    else
    {
        res->left = nullptr;
    }
    
    return res;
}

Function::Functree *Function::get_tree() const // CHECKED. Good
{
    return ftree->get_tree();
}

////////////////////////////////////////////////////////////
//--------------------Trigonometry------------------------//
////////////////////////////////////////////////////////////

Function Function::create_elemf_node(std::string functype) const // creating sin, cos etc. with "func" as its argument
{
    Function res = Function(); // Ftree.left is assigned nullptr in default ctor.
    res.ftree->value = functype;
    res.ftree->isvar = false;
    res.ftree->isnum = false;
    res.ftree->iselemfunc = true;
    res.arg = arg;
    res.ftree->right = get_tree();
    return res;
}

Function sin(const Function &arg)
{
    return arg.create_elemf_node("sin");
}

Function cos(const Function &arg)
{
    return arg.create_elemf_node("cos");
}

Function log(const Function &arg)
{
    return arg.create_elemf_node("log");
}

Function exp(const Function &arg)
{
    return arg.create_elemf_node("exp"); // TAYLOR LEFT TO DO
}

Function asin(const Function &arg)
{
    return arg.create_elemf_node("asin");
}
