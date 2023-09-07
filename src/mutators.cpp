#include "s21_matrix_oop.h"

int S21Matrix::getRows() {
    return rows_;
}

int S21Matrix::getCols() {
    return cols_;
}

void S21Matrix::addRows(int n) {
    if (n < 0) {
        throw std::invalid_argument("Incorrect number of rows");
    }
    double *new_matrix = new double[(rows_+n) * cols_];
    memset(new_matrix, 0, (rows_+n) * cols_ * sizeof(double));
    std::memcpy(new_matrix, matrix_, cols_ * rows_ * sizeof(double));
    delete [] matrix_;
    matrix_ = new_matrix;
    rows_ += n;
}

void S21Matrix::addCols(int n) {
    if (n < 0) {
        throw std::invalid_argument("Incorrect number of columns");
    }
    double *new_matrix = new double[rows_ * (cols_+n)];
    memset(new_matrix, 0, rows_ * (cols_+n) * sizeof(double));
    for (int i = 0; i < rows_; i++) {
        std::memcpy(new_matrix+(i*(cols_+n)), matrix_+(i*cols_), cols_ * sizeof(double));
    }
    delete [] matrix_;
    matrix_ = new_matrix;
    cols_ += n;
}

void S21Matrix::deleteRows(int n) {
    if (n < 0 || n >= rows_) {
        throw std::invalid_argument("Incorrect number of rows");
    }
    double *new_matrix = new double[(rows_-n) * cols_];
    memset(new_matrix, 0, (rows_-n) * cols_ * sizeof(double));
    std::memcpy(new_matrix, matrix_, cols_ * (rows_-n) * sizeof(double));
    delete [] matrix_;
    matrix_ = new_matrix;
    rows_ -= n;
}

void S21Matrix::deleteCols(int n) {
    if (n < 0 || n >= cols_) {
        throw std::invalid_argument("Incorrect number of columns");
    }
    int new_cols = cols_-n;
    double *new_matrix = new double[rows_ * new_cols];
    memset(new_matrix, 0, rows_ * new_cols * sizeof(double));
    for (int i = 0; i < rows_; i++) {
        std::memcpy(new_matrix+(i*new_cols), matrix_+(i*cols_), new_cols * sizeof(double));
    }
    delete [] matrix_;
    matrix_ = new_matrix;
    cols_ -= n;
}

void S21Matrix::set(int i, int j, double value) {
    if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    matrix_[i * cols_ + j] = value;
}
