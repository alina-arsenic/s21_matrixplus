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

int main() {
    S21Matrix cube;
    S21Matrix matrix(4, 5);
    S21Matrix another(matrix);
    cube.Print();
    matrix.Fill();
    matrix.Print();
    another.Fill();
    another.Print();
    S21Matrix result = matrix + another;
    result.Print();
    double num = matrix(1,2);
    std::cout << num << "\n";
    return 0;
}
