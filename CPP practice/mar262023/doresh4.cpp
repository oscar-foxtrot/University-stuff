//Task 4
#include <iostream>
#include <memory>

class DiagMatrix;

class SquareMatrix
{
public:
    SquareMatrix() {} // Empty body
    SquareMatrix(const std::initializer_list<std::initializer_list<double>> &lst);
    SquareMatrix(const std::unique_ptr<std::unique_ptr<double[]>[]> &arr, int matrix_order);
    void print_matrix() const;
    int get_order() const;
    virtual bool is_diag() const;
protected:
    int order;
private:
    std::unique_ptr<std::unique_ptr<double[]>[]> elems;

    friend DiagMatrix operator+(const DiagMatrix &matrix1, const DiagMatrix &matrix2);
    friend SquareMatrix operator+(const SquareMatrix &matrix1, const SquareMatrix &matrix2);
};

class DiagMatrix: public SquareMatrix
{
public:
    DiagMatrix() {}
    DiagMatrix(const std::initializer_list<double> &lst);
    DiagMatrix(const std::unique_ptr<double[]> &arr, int matrix_order);
    void print_matrix() const;
    bool is_diag() const;
private:
    std::unique_ptr<double[]> elems;

    friend DiagMatrix operator+(const DiagMatrix &matrix1, const DiagMatrix &matrix2);
    friend SquareMatrix operator+(const SquareMatrix &matrix1, const SquareMatrix &matrix2);
};

DiagMatrix operator+(const DiagMatrix &matrix1, const DiagMatrix &matrix2);
SquareMatrix operator+(const SquareMatrix &matrix1, const SquareMatrix &matrix2);


int main(int argc, char *argv[])
{
    std::cout << "Matrix 1 (SquareMatrix): ";
    SquareMatrix a({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    a.print_matrix();
    std::cout << "\n" << "Matrix 2 (SquareMatrix): ";
    SquareMatrix b({{1.2, 2.5}, {5.1, 9.12}});
    b.print_matrix();
    std::cout << "\n" << "Matrix 3 (DiagMatrix): ";
    DiagMatrix c({1.2, 2.5});
    c.print_matrix();

    std::cout << "\n\n";
    std::cout << "Matrix 2 + Matrix 2 = "; 
    (b + b).print_matrix();
    std::cout << "\nMatrix 2 + Matrix 3 = "; 
    (b + c).print_matrix();
    std::cout << "\nMatrix 3 + Matrix 3 = ";
    (c + c).print_matrix();
    std::cout << "\n(order 1 matrices) Matrix \"(1.25)\" + Matrix \"(2412.2)\" = ";
    (DiagMatrix({1.25}) + SquareMatrix({{2412.2}})).print_matrix();
    std::cout << "\nMatrix 1 + Matrix 1 = "; 
    (a + a).print_matrix();

    return 0;
}


SquareMatrix::SquareMatrix(const std::initializer_list<std::initializer_list<double>> &lst)
{
    order = lst.size();
    elems = std::unique_ptr<std::unique_ptr<double[]>[]> (new std::unique_ptr<double[]>[order]);
    for (int i = 0; i < order; ++i)
    {
        elems[i] = std::unique_ptr<double[]>(new double[order]);
    }

    int counter1 = 0;
    for (auto i: lst)
    {
        int counter2 = 0;
        for (auto j: i)
        {
            elems[counter1][counter2] = j;
            ++counter2;
        }
        ++counter1;
    }
}

SquareMatrix::SquareMatrix(const std::unique_ptr<std::unique_ptr<double[]>[]> &arr, int matrix_order): order(matrix_order) 
{
    elems = std::unique_ptr<std::unique_ptr<double[]>[]> (new std::unique_ptr<double[]>[order]);
    for (int i = 0; i < order; ++i)
    {
        elems[i] = std::unique_ptr<double[]>(new double[order]);
    }

    for (int i = 0; i < order; ++i)
    {
        for (int j = 0; j < order; ++j)
        {
            elems[i][j] = arr[i][j];
        }
    }
}
    
void SquareMatrix::print_matrix() const
{
    if (order == 0)
    {
        return;
    }

    std::cout << "{";
    for (int i = 0; i < order - 1; ++i)
    {
        std::cout << "{";
        for (int j = 0; j < order - 1; ++j)
        {
            std::cout << elems[i][j] << ", ";
        }
        std::cout << elems[i][order - 1] << "}, ";
    }
    std::cout << "{";
    for (int j = 0; j < order - 1; ++j)
    {
        std::cout << elems[order - 1][j] << ", ";
    }
    std::cout << elems[order - 1][order - 1] << "}}";
}

int SquareMatrix::get_order() const
{
    return order;
}

bool SquareMatrix::is_diag() const
{
    return false;
}

DiagMatrix::DiagMatrix(const std::initializer_list<double> &lst)
{
    order = lst.size();
    elems = std::unique_ptr<double[]>(new double[order]);

    int counter = 0;
    for (auto i: lst)
    {
        elems[counter] = i;
        ++counter;
    }
}

DiagMatrix::DiagMatrix(const std::unique_ptr<double[]> &arr, int matrix_order)
{
    order = matrix_order;
    elems = std::unique_ptr<double[]>(new double[order]);
    for (int i = 0; i < order; ++i)
    {
        elems[i] = arr[i];
    }
}

void DiagMatrix::print_matrix() const
{
    if (order == 0)
    {
        return;
    }

    std::cout << "{";
    for (int i = 0; i < order - 1; ++i)
    {
        std::cout << "{";
        for (int j = 0; j < order - 1; ++j)
        {
            if (i != j)
            {
                std::cout << "0, ";
            }
            else
            {
                std::cout << elems[i] << ", ";
            }
        }
        std::cout << "0}, ";
    }
    std::cout << "{";
    for (int j = 0; j < order - 1; ++j)
    {
        std::cout << "0, ";
    }
    std::cout << elems[order - 1] << "}}";
}

bool DiagMatrix::is_diag() const
{
    return true;
}    

DiagMatrix operator+(const DiagMatrix &matrix1, const DiagMatrix &matrix2)
{
    if (matrix1.order != matrix2.order)
    {
        std::cout << "Try with matrices with the same order\n";
        return DiagMatrix();
    }
    int order = matrix1.order;
    std::unique_ptr<double[]> tmp(new double[order]);
    for (int i = 0; i < order; ++i)
    {
        tmp[i] = matrix1.elems[i] + matrix2.elems[i];
    }
    return DiagMatrix(tmp, order);
}

SquareMatrix operator+(const SquareMatrix &matrix1, const SquareMatrix &matrix2)
{
    if (matrix1.order != matrix2.order)
    {
        std::cout << "Try with matrices with the same order\n";
        return SquareMatrix();
    }
    int order = matrix1.order;
    bool isdiag_matr1 = matrix1.is_diag();
    bool isdiag_matr2 = matrix2.is_diag();

    std::unique_ptr<std::unique_ptr<double[]>[]> tmp(new std::unique_ptr<double[]>[order]);
    for (int i = 0; i < order; ++i)
    {
        tmp[i] = std::unique_ptr<double[]>(new double[order]);
    }

    for (int i = 0; i < order; ++i)
    {
        for (int j = 0; j < order; ++j)
        {
            tmp[i][j] = isdiag_matr1 ? (i != j ? 0 : ((const DiagMatrix &)matrix1).elems[j]) : matrix1.elems[i][j];
            tmp[i][j] += isdiag_matr2 ? (i != j ? 0 : ((const DiagMatrix &)matrix2).elems[j]) : matrix2.elems[i][j];
        }
    }

    return SquareMatrix(tmp, order);
}
