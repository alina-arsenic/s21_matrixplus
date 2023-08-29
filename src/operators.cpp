#include "s21_matrix_oop.h"

// элемент по индексу
double S21Matrix::operator () (int row, int col) {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return matrix_[row * cols_ + col];
}

// сложение
S21Matrix S21Matrix::operator + (const S21Matrix& other) {
    if (other.rows_ != rows_ || other.cols_ != cols_) {
        throw std::invalid_argument("Incorrect input, matrices aren't the same size");
    }
    S21Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.matrix_[i * cols_ + j] = matrix_[i * cols_ + j] + other.matrix_[i * cols_ + j];
        }
    }
    return result;
}

// вычитание
S21Matrix S21Matrix::operator - (const S21Matrix& other) {
    if (other.rows_ != rows_ || other.cols_ != cols_) {
        throw std::invalid_argument("Incorrect input, matrices aren't the same size");
    }
    S21Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.matrix_[i * cols_ + j] = matrix_[i * cols_ + j] - other.matrix_[i * cols_ + j];
        }
    }
    return result;
}

// умножение на число
S21Matrix S21Matrix::operator * (double number) {
    S21Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.matrix_[i * cols_ + j] = matrix_[i * cols_ + j] * number;
        }
    }
    return result;
}

// умножение на матрицу
S21Matrix S21Matrix::operator * (const S21Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Incorrect input, number of columns of the first matrix must be equal to the number of rows of the second one");
    }
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            result.matrix_[i * other.cols_ + j] = 0;
            for (int k = 0; k < cols_; k++) {
                result.matrix_[i * other.cols_ + j] += matrix_[i * cols_ + k] * other.matrix_[k * other.cols_ + j];
            }
        }
    }
    return result;

}

// проверка равенства
bool S21Matrix::operator == (const S21Matrix& other) {
    bool equal = false;
    if (rows_ == other.rows_ && cols_ == other.cols_) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                equal = (matrix_[i * cols_ + j] == other.matrix_[i * cols_ + j]);
                if (!equal)
                    break;
            }
        }
    }
    return equal;
}

// присвоение
S21Matrix& S21Matrix::operator = (const S21Matrix& other) {
    if (rows_ * cols_ == other.rows_ * other.cols_) {
        std::memcpy(matrix_, other.matrix_, other.cols_ * other.rows_ * sizeof(double));
    } else {
        delete [] matrix_;
        matrix_ = new double[other.rows_ * other.cols_]();
        std::memcpy(matrix_, other.matrix_, other.cols_ * other.rows_ * sizeof(double));
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    return *this;
}

// сложение с присвоением
S21Matrix& S21Matrix::operator += (const S21Matrix& other) {
    if (other.rows_ != rows_ || other.cols_ != cols_) {
        throw std::invalid_argument("Incorrect input, matrices aren't the same size");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i * cols_ + j] += other.matrix_[i * cols_ + j];
        }
    }
    return *this;
}

// вычитание с присвоением
S21Matrix& S21Matrix::operator -= (const S21Matrix& other) {
    if (other.rows_ != rows_ || other.cols_ != cols_) {
        throw std::invalid_argument("Incorrect input, matrices aren't the same size");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i * cols_ + j] -= other.matrix_[i * cols_ + j];
        }
    }
    return *this;
}

//умножение на число с присвоением
S21Matrix& S21Matrix::operator *= (double number) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i * cols_ + j] *= number;
        }
    }
    return *this;
}

// умножение на матрицу с присвоением
S21Matrix& S21Matrix::operator *= (const S21Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Incorrect input, number of columns of the first matrix must be equal to the number of rows of the second one");
    }
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            result.matrix_[i * other.cols_ + j] = 0;
            for (int k = 0; k < cols_; k++) {
                result.matrix_[i * other.cols_ + j] += matrix_[i * cols_ + k] * other.matrix_[k * other.cols_ + j];
            }
        }
    }
    *this = result;
    return *this;
}
