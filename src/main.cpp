#include "s21_matrix_oop.h"

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
