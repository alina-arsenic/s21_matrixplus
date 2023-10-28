#include "s21_matrix_oop.h"

void S21Matrix::Print() {
  int tol = 8;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << round(matrix_[i * cols_ + j] * pow(10, tol)) / pow(10, tol)
                << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void S21Matrix::Read(const char *matrix_str) {
  char str[strlen(matrix_str)];
  strcpy(str, matrix_str);
  char *ptr = std::strtok(str, " \n\t");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      sscanf(ptr, "%lf", &matrix_[i * cols_ + j]);
      ptr = std::strtok(nullptr, " \n\t");
    }
  }
}
