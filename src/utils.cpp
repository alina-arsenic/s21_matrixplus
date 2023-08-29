#include "s21_matrix_oop.h"

void S21Matrix::Print() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << std::setw(4) << matrix_[i * cols_ + j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void S21Matrix::Fill() {
    double count = 0;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i * cols_ + j] = count++;
        }
    }
}
