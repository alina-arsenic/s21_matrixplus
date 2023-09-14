#include "s21_matrix_oop.h"

// Проверяет матрицы на равенство между собой
bool S21Matrix::EqMatrix(const S21Matrix& other) { return *this == other; }

// Прибавляет вторую матрицы к текущей
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (other.rows_ != rows_ || other.cols_ != cols_) {
    throw std::invalid_argument(
        "Incorrect input, matrices aren't the same size");
  }
  *this += other;
}

// Вычитает из текущей матрицы другую
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (other.rows_ != rows_ || other.cols_ != cols_) {
    throw std::invalid_argument(
        "Incorrect input, matrices aren't the same size");
  }
  *this -= other;
}

// Умножает текущую матрицу на число
void S21Matrix::MulNumber(const double num) { *this *= num; }

// Умножает текущую матрицу на вторую
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Incorrect input, number of columns of the first matrix must be equal "
        "to the number of rows of the second one");
  }
  *this *= other;
}

// Создает новую транспонированную матрицу из текущей и возвращает ее
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      result.Set(i, j, matrix_[j * cols_ + i]);
    }
  }
  *this = result;
  return *this;
}

// Возвращает минор элемента матрицы
S21Matrix S21Matrix::Minor(int row, int col) {
  int cols = cols_ - 1;
  int rows = rows_ - 1;
  if (cols < 1 || rows < 1) {
    throw std::invalid_argument("Minor of the element does not exist");
  }
  S21Matrix minor(rows, cols);
  int iShift = 0, jShift = 0;
  for (int i = 0; i < rows; i++) {
    iShift = i >= row;
    for (int j = 0; j < cols; j++) {
      jShift = j >= col;
      minor.Set(i, j, matrix_[(i + iShift) * cols_ + j + jShift]);
    }
  }
  return minor;
}

// Возвращает матрицу алгебраических дополнений
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Incorrect input, the matrix isnt't square");
  }
  S21Matrix result(rows_, cols_);
  S21Matrix self(*this);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = self.Minor(i, j);
      result.Set(i, j, pow(-1, i + j) * minor.Determinant());
    }
  }
  return result;
}

// Привести матрицу к верхнетреугольному виду, вернуть количество перестановок
// рядов
int S21Matrix::MakeTriangle() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Incorrect input, the matrix isnt't square");
  }
  int swap_count = 0;
  int n = cols_;
  for (int i = 0; i < n - 1; i++) {
    for (int k = i + 1; k < n; k++) {
      if (fabs(matrix_[i * n + i]) < fabs(matrix_[k * n + i])) {
        swap_count += 1;
        for (int j = 0; j < n; j++) {
          double temp = matrix_[i * n + j];
          matrix_[i * n + j] = matrix_[k * n + j];
          matrix_[k * n + j] = temp;
        }
      }
    }
    for (int k = i + 1; k < n; k++) {
      if (matrix_[i * n + i] != 0) {
        long double coef = (long double)matrix_[k * n + i] / matrix_[i * n + i];
        for (int j = 0; j < n; j++) {
          matrix_[k * n + j] -= coef * matrix_[i * n + j];
        }
      }
    }
  }
  return swap_count;
}

// Вычисляет и возвращает определитель текущей матрицы
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Incorrect input, the matrix isnt't square");
  }
  double determinant = 1;
  S21Matrix triangle(*this);
  int swap_count = triangle.MakeTriangle();
  for (int i = 0; i < rows_; i++) {
    determinant *= triangle(i, i);
  }
  determinant *= pow(-1, swap_count);
  return determinant;
}

// Вычисляет и возвращает обратную матрицу
S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Incorrect input, the matrix isnt't square");
  } else if (this->Determinant() == 0) {
    throw std::invalid_argument("The determinant of the matrix is 0");
  }
  S21Matrix result = this->CalcComplements();
  result.Transpose();
  result *= 1 / this->Determinant();
  return result;
}
