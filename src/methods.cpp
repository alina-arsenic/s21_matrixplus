#include "s21_matrix_oop.h"

// Проверяет матрицы на равенство между собой
bool S21Matrix::EqMatrix(const S21Matrix& other) {
    return *this == other;
}

// Прибавляет вторую матрицы к текущей
void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (other.rows_ != rows_ || other.cols_ != cols_) {
        throw std::invalid_argument("Incorrect input, matrices aren't the same size");
    }
    *this += other;
}

// Вычитает из текущей матрицы другую
void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (other.rows_ != rows_ || other.cols_ != cols_) {
        throw std::invalid_argument("Incorrect input, matrices aren't the same size");
    }
    *this -= other;
}

// Умножает текущую матрицу на число
void S21Matrix::MulNumber(const double num) {
    *this *= num;
}

// Умножает текущую матрицу на вторую
void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Incorrect input, number of columns of the first matrix must be equal to the number of rows of the second one");
    }
    *this *= other;
}

// Создает новую транспонированную матрицу из текущей и возвращает ее
S21Matrix S21Matrix::Transpose() {
    //
}

// Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
S21Matrix S21Matrix::CalcComplements() {
    //
}

// Вычисляет и возвращает определитель текущей матрицы
double S21Matrix::Determinant() {
    //
}

// Вычисляет и возвращает обратную матрицу
S21Matrix S21Matrix::InverseMatrix() {
    //
}
