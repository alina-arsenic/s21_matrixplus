#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

class S21Matrix {
 private:
  // attributes
  int rows_, cols_;
  double* matrix_;

 public:
  // constructors and destructors
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  // accessors and mutators
  int GetRows();
  int GetCols();
  void AddRows(int n);
  void AddCols(int n);
  void DeleteRows(int n);
  void DeleteCols(int n);
  void Set(int i, int j, double value);

  // operators overloads
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(double number);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(double number);
  S21Matrix& operator*=(const S21Matrix& other);
  double operator()(int row, int col);

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

  // utility methods
  int MakeTriangle();
  S21Matrix Minor(int row, int col);
  void Print();
  void Read(const char* matrix_str);
};

#endif  // __S21MATRIX_H__
