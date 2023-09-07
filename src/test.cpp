#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "s21_matrix_oop.h"

using namespace std;

int elements_are_zeroes(S21Matrix matrix) {
  int ok = 1;
  for (int i = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getCols(); j++) {
      if (matrix(i,j) != 0) {
        std::cout << matrix(i,j) << " ";
        ok = 0; break;
      }
    }
  }
  return ok;
}

TEST(ConstructorsTest, Basic) {
  S21Matrix a;
  ASSERT_TRUE(a.getCols() == 3);
  ASSERT_TRUE(a.getRows() == 3);
  ASSERT_TRUE(elements_are_zeroes(a) == 1);
}

TEST(ConstructorsTest, Parametric) {
  int error;

  S21Matrix a(7, 8);
  ASSERT_TRUE(a.getCols() == 8);
  ASSERT_TRUE(a.getRows() == 7);
  ASSERT_TRUE(elements_are_zeroes(a) == 1);
  
  error = 0;
  try {
    S21Matrix b(-7, -8);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  error = 0;
  try {
    S21Matrix c(6, 0);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

}

TEST(ConstructorsTest, Copying) {
  S21Matrix a(7, 8);
  a.Fill();
  S21Matrix b(a);
  ASSERT_TRUE(a == b);
}

TEST(ConstructorsTest, Moving) {
  S21Matrix a = S21Matrix(7, 8);
  ASSERT_TRUE(a.getCols() == 8);
  ASSERT_TRUE(a.getRows() == 7);
  ASSERT_TRUE(elements_are_zeroes(a) == 1);
}

TEST(MutatorsTest, RowsCols) {
  int error;

  S21Matrix a(4, 4);
  a.Fill();
  S21Matrix b(a);
  a.addCols(9);
  a.deleteCols(3);
  a.deleteCols(0);
  a.addRows(0);
  a.addRows(5);
  a.deleteRows(2);
  ASSERT_TRUE(a.getCols() == 10);
  ASSERT_TRUE(a.getRows() == 7);
  a.deleteCols(6);
  a.deleteRows(3);
  ASSERT_TRUE(a == b);

  error = 0;
  try {
    S21Matrix c;
    c.deleteCols(3);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  error = 0;
  try {
    S21Matrix d;
    d.deleteRows(-4);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);
}

TEST(MutatorsTest, Elements) {
  S21Matrix a(4, 4);
  a.Fill();
  a.set(0,1, 123.456);
  ASSERT_TRUE(a(0,1) == 123.456);

  int error = 0;
  try {
    S21Matrix b;
    b.set(7,1, 123.456);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  error = 0;
  try {
    S21Matrix c;
    c.set(1,-4, 123.456);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);
}

TEST(OperatorsTest, Addition) {
  S21Matrix a(3, 3);
  a.Fill();
  S21Matrix b(3, 2);
  b.Fill();
  S21Matrix c;

  int error = 0;
  try {
    c = a + b;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  b.addCols(1);
  c = a + b;

  ASSERT_TRUE(c(0,0) == 0);
  ASSERT_TRUE(c(0,1) == 2);
  ASSERT_TRUE(c(0,2) == 2);
  ASSERT_TRUE(c(1,0) == 5);
  ASSERT_TRUE(c(1,1) == 7);
  ASSERT_TRUE(c(1,2) == 5);
  ASSERT_TRUE(c(2,0) == 10);
  ASSERT_TRUE(c(2,1) == 12);
  ASSERT_TRUE(c(2,2) == 8);

}

TEST(OperatorsTest, Subtraction) {
  S21Matrix a(3, 1);
  a.Fill();
  S21Matrix b(3, 3);
  b.Fill();
  S21Matrix c;

  int error = 0;
  try {
    c = a - b;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  a.addCols(2);
  c = a - b;

  ASSERT_TRUE(c(0,0) == 0);
  ASSERT_TRUE(c(0,1) == -1);
  ASSERT_TRUE(c(0,2) == -2);
  ASSERT_TRUE(c(1,0) == -2);
  ASSERT_TRUE(c(1,1) == -4);
  ASSERT_TRUE(c(1,2) == -5);
  ASSERT_TRUE(c(2,0) == -4);
  ASSERT_TRUE(c(2,1) == -7);
  ASSERT_TRUE(c(2,2) == -8);

}

TEST(OperatorsTest, MultiplicationNumber) {
  S21Matrix a;
  a.Fill();
  S21Matrix b = a * 3;

  ASSERT_TRUE(b(0,0) == 0);
  ASSERT_TRUE(b(0,1) == 3);
  ASSERT_TRUE(b(0,2) == 6);
  ASSERT_TRUE(b(1,0) == 9);
  ASSERT_TRUE(b(1,1) == 12);
  ASSERT_TRUE(b(1,2) == 15);
  ASSERT_TRUE(b(2,0) == 18);
  ASSERT_TRUE(b(2,1) == 21);
  ASSERT_TRUE(b(2,2) == 24);

}

TEST(OperatorsTest, MultiplicationMatrix) {
  S21Matrix a(3, 2);
  a.Fill();
  S21Matrix b(2, 3);
  b.Fill();
  S21Matrix c = a * b;

  ASSERT_TRUE(c(0,0) == 3);
  ASSERT_TRUE(c(0,1) == 4);
  ASSERT_TRUE(c(0,2) == 5);
  ASSERT_TRUE(c(1,0) == 9);
  ASSERT_TRUE(c(1,1) == 14);
  ASSERT_TRUE(c(1,2) == 19);
  ASSERT_TRUE(c(2,0) == 15);
  ASSERT_TRUE(c(2,1) == 24);
  ASSERT_TRUE(c(2,2) == 33);

  S21Matrix d(2,5), e(4,3);
  int error = 0;
  try {
    S21Matrix f = d * e;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

}

TEST(OperatorsTest, Equality) {
  S21Matrix a, b;
  a.Fill(); b.Fill();
  ASSERT_TRUE((a == b) == 1);

  S21Matrix c(3,4);
  ASSERT_TRUE((a == c) == 0);

  c.Fill();
  c.deleteCols(1);
  ASSERT_TRUE((a == c) == 0);
}

TEST(OperatorsTest, AdditionAssignment) {
  S21Matrix a(3, 3);
  a.Fill();
  S21Matrix b(3, 2);
  b.Fill();

  int error = 0;
  try {
    a += b;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  b.addCols(1);
  a += b;

  ASSERT_TRUE(a(0,0) == 0);
  ASSERT_TRUE(a(0,1) == 2);
  ASSERT_TRUE(a(0,2) == 2);
  ASSERT_TRUE(a(1,0) == 5);
  ASSERT_TRUE(a(1,1) == 7);
  ASSERT_TRUE(a(1,2) == 5);
  ASSERT_TRUE(a(2,0) == 10);
  ASSERT_TRUE(a(2,1) == 12);
  ASSERT_TRUE(a(2,2) == 8);

}

TEST(OperatorsTest, SubtractionAssignment) {
  S21Matrix a(3, 1);
  a.Fill();
  S21Matrix b(3, 3);
  b.Fill();

  int error = 0;
  try {
    a -= b;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  a.addCols(2);
  a -= b;

  ASSERT_TRUE(a(0,0) == 0);
  ASSERT_TRUE(a(0,1) == -1);
  ASSERT_TRUE(a(0,2) == -2);
  ASSERT_TRUE(a(1,0) == -2);
  ASSERT_TRUE(a(1,1) == -4);
  ASSERT_TRUE(a(1,2) == -5);
  ASSERT_TRUE(a(2,0) == -4);
  ASSERT_TRUE(a(2,1) == -7);
  ASSERT_TRUE(a(2,2) == -8);

}

TEST(OperatorsTest, MultiplicationNumberAssignment) {
  S21Matrix a;
  a.Fill();
  a *= 3;

  ASSERT_TRUE(a(0,0) == 0);
  ASSERT_TRUE(a(0,1) == 3);
  ASSERT_TRUE(a(0,2) == 6);
  ASSERT_TRUE(a(1,0) == 9);
  ASSERT_TRUE(a(1,1) == 12);
  ASSERT_TRUE(a(1,2) == 15);
  ASSERT_TRUE(a(2,0) == 18);
  ASSERT_TRUE(a(2,1) == 21);
  ASSERT_TRUE(a(2,2) == 24);

}

TEST(OperatorsTest, MultiplicationMatrixAssignment) {
  S21Matrix a(3, 2);
  a.Fill();
  S21Matrix b(2, 3);
  b.Fill();
  a *= b;

  ASSERT_TRUE(a(0,0) == 3);
  ASSERT_TRUE(a(0,1) == 4);
  ASSERT_TRUE(a(0,2) == 5);
  ASSERT_TRUE(a(1,0) == 9);
  ASSERT_TRUE(a(1,1) == 14);
  ASSERT_TRUE(a(1,2) == 19);
  ASSERT_TRUE(a(2,0) == 15);
  ASSERT_TRUE(a(2,1) == 24);
  ASSERT_TRUE(a(2,2) == 33);

  S21Matrix d(2,5), e(4,3);
  int error = 0;
  try {
    d *= e;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
