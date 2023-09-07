#include "s21_matrix_oop.h"

// Базовый конструктор
S21Matrix::S21Matrix() {
    rows_ = 3;
    cols_ = 3;
    matrix_ = new double[rows_ * cols_];
    memset(matrix_, 0, rows_ * cols_ * sizeof(double));
}

// Параметризированный конструктор
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Incorrect sizes of the matrix");
    }
    matrix_ = new double[rows_ * cols_];
    memset(matrix_, 0, rows_ * cols_ * sizeof(double));
}

// Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    matrix_ = new double[rows_ * cols_];
    std::memcpy(matrix_, other.matrix_, cols_ * rows_ * sizeof(double));
}

// Конструктор переноса
S21Matrix::S21Matrix(S21Matrix&& other) {
    if (rows_ * cols_ != other.rows_ * other.cols_) {
        delete [] matrix_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        matrix_ = new double[other.rows_ * other.cols_];
    }
    std::memcpy(matrix_, other.matrix_, cols_ * rows_ * sizeof(double));
    delete [] other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
}

// Деструктор
S21Matrix::~S21Matrix() {
    if (matrix_) delete [] matrix_;
}
