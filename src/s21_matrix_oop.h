#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>
#include <iomanip>
#include <cstring>

class S21Matrix {
private:
    // attributes
    int rows_, cols_;
    double *matrix_;

public:

    // constructors and destructors
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    // accessors and mutators
    int getRows();
    int getCols();
    void addRows(int n);
    void addCols(int n);
    void deleteRows(int n);
    void deleteCols(int n);
    void set(int i, int j, double value);

    // operators overloads
    S21Matrix operator + (const S21Matrix& other);
    S21Matrix operator - (const S21Matrix& other);
    S21Matrix operator * (double number);
    S21Matrix operator * (const S21Matrix& other);
    bool operator == (const S21Matrix& other);
    S21Matrix& operator = (const S21Matrix& other);
    S21Matrix& operator += (const S21Matrix& other);
    S21Matrix& operator -= (const S21Matrix& other);
    S21Matrix& operator *= (double number);
    S21Matrix& operator *= (const S21Matrix& other);
    double operator () (int row, int col);

    // public methods
    bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();

    void Print();
    void Fill();

};

#endif  // __S21MATRIX_H__
