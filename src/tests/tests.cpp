#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

using namespace std;

int elements_are_zeroes(S21Matrix matrix) {
  int ok = 1;
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      if (matrix(i, j) != 0) {
        std::cout << matrix(i, j) << " ";
        ok = 0;
        break;
      }
    }
  }
  return ok;
}

TEST(ConstructorsTest, Basic) {
  S21Matrix a;
  ASSERT_TRUE(a.GetCols() == 3);
  ASSERT_TRUE(a.GetRows() == 3);
  ASSERT_TRUE(elements_are_zeroes(a) == 1);
}

TEST(ConstructorsTest, Parametric) {
  int error;

  error = 0;
  try {
    S21Matrix b(0, 0);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  S21Matrix a(70, 80);
  ASSERT_TRUE(a.GetCols() == 80);
  ASSERT_TRUE(a.GetRows() == 70);
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
  S21Matrix a(2, 3);
  a.Read(
      "958.02 -964.03 -225.63 \
  169.36 307.93 -746.34");
  S21Matrix b(a);
  ASSERT_TRUE(a == b);
}

TEST(ConstructorsTest, Moving) {
  S21Matrix a = S21Matrix(7, 8);
  ASSERT_TRUE(a.GetCols() == 8);
  ASSERT_TRUE(a.GetRows() == 7);
  ASSERT_TRUE(elements_are_zeroes(a) == 1);
}

TEST(MutatorsTest, RowsCols) {
  int error;

  S21Matrix a(4, 4);
  S21Matrix b(a);
  a.AddCols(9);
  a.DeleteCols(3);
  a.DeleteCols(0);
  a.AddRows(0);
  a.AddRows(5);
  a.DeleteRows(2);
  ASSERT_TRUE(a.GetCols() == 10);
  ASSERT_TRUE(a.GetRows() == 7);
  a.DeleteCols(6);
  a.DeleteRows(3);
  ASSERT_TRUE(a == b);

  error = 0;
  try {
    S21Matrix c;
    c.DeleteCols(3);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  error = 0;
  try {
    S21Matrix d;
    d.DeleteRows(-4);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);
}

TEST(MutatorsTest, Elements) {
  S21Matrix a(4, 4);
  a.Set(0, 1, 123.456);
  ASSERT_TRUE(a(0, 1) == 123.456);

  int error = 0;
  try {
    S21Matrix b;
    b.Set(7, 1, 123.456);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  error = 0;
  try {
    S21Matrix c;
    c.Set(1, -4, 123.456);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);
}

TEST(OperatorsTest, Addition) {
  S21Matrix a(5, 5);
  a.Read(
      "293.42 641.38 -546.28 394.64 965.58 \
  889.73 -520.53 -537.25 -717.97 -391.36 \
  -741.01 -862.27 941.29 -201.70 -941.59 \
  941.73 -916.94 -787.49 -209.67 416.92 \
  -974.87 841.04 -391.81 897.30 245.85");
  S21Matrix b(5, 4);
  S21Matrix c;

  int error = 0;
  try {
    c = a + b;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  b.AddCols(1);
  b.Read(
      "-291.85 733.25 264.21 -370.24 905.22 \
  -322.03 834.46 485.54 -304.69 -116.80 \
  -649.31 278.75 -593.67 -735.50 938.93 \
  788.90 652.48 -114.72 41.42 495.57 \
  589.38 -643.13 -859.12 368.61 -926.47");
  c = a + b;

  S21Matrix answer(5, 5);
  answer.Read(
      "1.57 1374.63 -282.07 24.4 1870.8 \
  567.7 313.93 -51.71 -1022.66 -508.16 \
  -1390.32 -583.52 347.62 -937.2 -2.66 \
  1730.63 -264.46 -902.21 -168.25 912.49 \
  -385.49 197.91 -1250.93 1265.91 -680.62");

  ASSERT_TRUE(c == answer);
}

TEST(OperatorsTest, Subtraction) {
  S21Matrix a(5, 5);
  a.Read(
      "293.42 641.38 -546.28 394.64 965.58 \
  889.73 -520.53 -537.25 -717.97 -391.36 \
  -741.01 -862.27 941.29 -201.70 -941.59 \
  941.73 -916.94 -787.49 -209.67 416.92 \
  -974.87 841.04 -391.81 897.30 245.85");
  S21Matrix b(5, 4);
  S21Matrix c;

  int error = 0;
  try {
    c = a - b;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  b.AddCols(1);
  b.Read(
      "-291.85 733.25 264.21 -370.24 905.22 \
  -322.03 834.46 485.54 -304.69 -116.80 \
  -649.31 278.75 -593.67 -735.50 938.93 \
  788.90 652.48 -114.72 41.42 495.57 \
  589.38 -643.13 -859.12 368.61 -926.47");
  c = a - b;

  S21Matrix answer(5, 5);
  answer.Read(
      "585.27 -91.87 -810.49 764.88 60.36 \
  1211.76 -1354.99 -1022.79 -413.28 -274.56 \
  -91.7 -1141.02 1534.96 533.8 -1880.52 \
  152.83 -1569.42 -672.77 -251.09 -78.65 \
  -1564.25 1484.17 467.31 528.69 1172.32");
  ASSERT_TRUE(c == answer);
}

TEST(OperatorsTest, MultiplicationNumber) {
  S21Matrix a(5, 5);
  a.Read(
      "293.42 641.38 -546.28 394.64 965.58 \
  889.73 -520.53 -537.25 -717.97 -391.36 \
  -741.01 -862.27 941.29 -201.70 -941.59 \
  941.73 -916.94 -787.49 -209.67 416.92 \
  -974.87 841.04 -391.81 897.30 245.85");
  S21Matrix b = a * -3;
  S21Matrix answer(5, 5);
  answer.Read(
      "-880.26 -1924.14 1638.84 -1183.92 -2896.74 \
  -2669.19 1561.59 1611.75 2153.91 1174.08 \
  2223.03 2586.81 -2823.87 605.1 2824.77 \
  -2825.19 2750.82 2362.47 629.01 -1250.76 \
  2924.61 -2523.12 1175.43 -2691.9 -737.55");
  ASSERT_TRUE(b == answer);
}

TEST(OperatorsTest, MultiplicationMatrix) {
  S21Matrix a(4, 4);
  a.Read(
      "-254.02 858.34 323.74 546.57 \
  94.14 -309.69 827.03 250.70 \
  -833.86 542.57 470.06 -832.96 \
  421.63 -817.36 -640.60 -882.07");
  S21Matrix b(4, 3);
  b.Read(
      "-674.59 -316.84 441.49 \
  -875.55 -955.93 819.56 \
  991.36 -802.33 367.04 \
  283.03 452.45 -787.10");
  S21Matrix c = a * b;
  S21Matrix answer(4, 3);
  answer.Read(
      "-104521.64169999998 -752479.9771 279934.1232 \
  1098483.2587 -283907.12080000003 -106020.54659999997 \
  317712.4667 -1008474.7295	904681.4562 \
  -453505.3218000001 762629.7220999999 -24578.659900000086");
  ASSERT_TRUE(c == answer);

  S21Matrix d(2, 5), e(4, 3);
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
  ASSERT_TRUE((a == b) == 1);

  S21Matrix c(3, 4);
  ASSERT_TRUE((a == c) == 0);

  c.DeleteCols(1);
  ASSERT_TRUE((a == c) == 1);
}

TEST(OperatorsTest, AdditionAssignment) {
  S21Matrix a(5, 5);
  a.Read(
      "293.42 641.38 -546.28 394.64 965.58 \
  889.73 -520.53 -537.25 -717.97 -391.36 \
  -741.01 -862.27 941.29 -201.70 -941.59 \
  941.73 -916.94 -787.49 -209.67 416.92 \
  -974.87 841.04 -391.81 897.30 245.85");
  S21Matrix b(5, 4);

  int error = 0;
  try {
    a += b;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  b.AddCols(1);
  b.Read(
      "-291.85 733.25 264.21 -370.24 905.22 \
  -322.03 834.46 485.54 -304.69 -116.80 \
  -649.31 278.75 -593.67 -735.50 938.93 \
  788.90 652.48 -114.72 41.42 495.57 \
  589.38 -643.13 -859.12 368.61 -926.47");
  a += b;

  S21Matrix answer(5, 5);
  answer.Read(
      "1.57 1374.63 -282.07 24.4 1870.8 \
  567.7 313.93 -51.71 -1022.66 -508.16 \
  -1390.32 -583.52 347.62 -937.2 -2.66 \
  1730.63 -264.46 -902.21 -168.25 912.49 \
  -385.49 197.91 -1250.93 1265.91 -680.62");

  ASSERT_TRUE(a == answer);
}

TEST(OperatorsTest, SubtractionAssignment) {
  S21Matrix a(5, 5);
  a.Read(
      "293.42 641.38 -546.28 394.64 965.58 \
  889.73 -520.53 -537.25 -717.97 -391.36 \
  -741.01 -862.27 941.29 -201.70 -941.59 \
  941.73 -916.94 -787.49 -209.67 416.92 \
  -974.87 841.04 -391.81 897.30 245.85");
  S21Matrix b(5, 4);

  int error = 0;
  try {
    a -= b;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  b.AddCols(1);
  b.Read(
      "-291.85 733.25 264.21 -370.24 905.22 \
  -322.03 834.46 485.54 -304.69 -116.80 \
  -649.31 278.75 -593.67 -735.50 938.93 \
  788.90 652.48 -114.72 41.42 495.57 \
  589.38 -643.13 -859.12 368.61 -926.47");
  a -= b;

  S21Matrix answer(5, 5);
  answer.Read(
      "585.27 -91.87 -810.49 764.88 60.36 \
  1211.76 -1354.99 -1022.79 -413.28 -274.56 \
  -91.7 -1141.02 1534.96 533.8 -1880.52 \
  152.83 -1569.42 -672.77 -251.09 -78.65 \
  -1564.25 1484.17 467.31 528.69 1172.32");
  ASSERT_TRUE(a == answer);
}

TEST(OperatorsTest, MultiplicationNumberAssignment) {
  S21Matrix a(5, 5);
  a.Read(
      "293.42 641.38 -546.28 394.64 965.58 \
  889.73 -520.53 -537.25 -717.97 -391.36 \
  -741.01 -862.27 941.29 -201.70 -941.59 \
  941.73 -916.94 -787.49 -209.67 416.92 \
  -974.87 841.04 -391.81 897.30 245.85");
  a *= -3;
  S21Matrix answer(5, 5);
  answer.Read(
      "-880.26 -1924.14 1638.84 -1183.92 -2896.74 \
  -2669.19 1561.59 1611.75 2153.91 1174.08 \
  2223.03 2586.81 -2823.87 605.1 2824.77 \
  -2825.19 2750.82 2362.47 629.01 -1250.76 \
  2924.61 -2523.12 1175.43 -2691.9 -737.55");
  ASSERT_TRUE(a == answer);
}

TEST(OperatorsTest, MultiplicationMatrixAssignment) {
  S21Matrix a(4, 4);
  a.Read(
      "-254.02 858.34 323.74 546.57 \
  94.14 -309.69 827.03 250.70 \
  -833.86 542.57 470.06 -832.96 \
  421.63 -817.36 -640.60 -882.07");
  S21Matrix b(4, 3);
  b.Read(
      "-674.59 -316.84 441.49 \
  -875.55 -955.93 819.56 \
  991.36 -802.33 367.04 \
  283.03 452.45 -787.10");
  a *= b;
  S21Matrix answer(4, 3);
  answer.Read(
      "-104521.64169999998 -752479.9771 279934.1232 \
  1098483.2587 -283907.12080000003 -106020.54659999997 \
  317712.4667 -1008474.7295	904681.4562 \
  -453505.3218000001 762629.7220999999 -24578.659900000086");
  ASSERT_TRUE(a == answer);

  S21Matrix d(2, 5), e(4, 3);
  int error = 0;
  try {
    d *= e;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);
}

TEST(MethodsTest, EqualityMethod) {
  S21Matrix a, b;
  ASSERT_TRUE(a.EqMatrix(b) == true);

  S21Matrix c(3, 4);
  ASSERT_TRUE(a.EqMatrix(c) == false);

  c.DeleteCols(1);
  ASSERT_TRUE(a.EqMatrix(c) == true);
}

TEST(MethodsTest, AdditionMethod) {
  S21Matrix a(5, 5);
  a.Read(
      "293.42 641.38 -546.28 394.64 965.58 \
  889.73 -520.53 -537.25 -717.97 -391.36 \
  -741.01 -862.27 941.29 -201.70 -941.59 \
  941.73 -916.94 -787.49 -209.67 416.92 \
  -974.87 841.04 -391.81 897.30 245.85");
  S21Matrix b(5, 4);

  int error = 0;
  try {
    a.SumMatrix(b);
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  b.AddCols(1);
  b.Read(
      "-291.85 733.25 264.21 -370.24 905.22 \
  -322.03 834.46 485.54 -304.69 -116.80 \
  -649.31 278.75 -593.67 -735.50 938.93 \
  788.90 652.48 -114.72 41.42 495.57 \
  589.38 -643.13 -859.12 368.61 -926.47");
  a.SumMatrix(b);

  S21Matrix answer(5, 5);
  answer.Read(
      "1.57 1374.63 -282.07 24.4 1870.8 \
  567.7 313.93 -51.71 -1022.66 -508.16 \
  -1390.32 -583.52 347.62 -937.2 -2.66 \
  1730.63 -264.46 -902.21 -168.25 912.49 \
  -385.49 197.91 -1250.93 1265.91 -680.62");

  ASSERT_TRUE(a == answer);
}

TEST(MethodsTest, SubtractionMethod) {
  S21Matrix a(5, 5);
  a.Read(
      "293.42 641.38 -546.28 394.64 965.58 \
  889.73 -520.53 -537.25 -717.97 -391.36 \
  -741.01 -862.27 941.29 -201.70 -941.59 \
  941.73 -916.94 -787.49 -209.67 416.92 \
  -974.87 841.04 -391.81 897.30 245.85");
  S21Matrix b(5, 4);

  int error = 0;
  try {
    a -= b;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  b.AddCols(1);
  b.Read(
      "-291.85 733.25 264.21 -370.24 905.22 \
  -322.03 834.46 485.54 -304.69 -116.80 \
  -649.31 278.75 -593.67 -735.50 938.93 \
  788.90 652.48 -114.72 41.42 495.57 \
  589.38 -643.13 -859.12 368.61 -926.47");
  a -= b;

  S21Matrix answer(5, 5);
  answer.Read(
      "585.27 -91.87 -810.49 764.88 60.36 \
  1211.76 -1354.99 -1022.79 -413.28 -274.56 \
  -91.7 -1141.02 1534.96 533.8 -1880.52 \
  152.83 -1569.42 -672.77 -251.09 -78.65 \
  -1564.25 1484.17 467.31 528.69 1172.32");
  ASSERT_TRUE(a == answer);
}

TEST(MethodsTest, MultiplicationNumberMethod) {
  S21Matrix a(5, 5);
  a.Read(
      "293.42 641.38 -546.28 394.64 965.58 \
  889.73 -520.53 -537.25 -717.97 -391.36 \
  -741.01 -862.27 941.29 -201.70 -941.59 \
  941.73 -916.94 -787.49 -209.67 416.92 \
  -974.87 841.04 -391.81 897.30 245.85");
  a.MulNumber(-3);
  S21Matrix answer(5, 5);
  answer.Read(
      "-880.26 -1924.14 1638.84 -1183.92 -2896.74 \
  -2669.19 1561.59 1611.75 2153.91 1174.08 \
  2223.03 2586.81 -2823.87 605.1 2824.77 \
  -2825.19 2750.82 2362.47 629.01 -1250.76 \
  2924.61 -2523.12 1175.43 -2691.9 -737.55");
  ASSERT_TRUE(a == answer);
}

TEST(MethodsTest, MultiplicationMatrixMethod) {
  S21Matrix a(4, 4);
  a.Read(
      "-254.02 858.34 323.74 546.57 \
  94.14 -309.69 827.03 250.70 \
  -833.86 542.57 470.06 -832.96 \
  421.63 -817.36 -640.60 -882.07");
  S21Matrix b(4, 3);
  b.Read(
      "-674.59 -316.84 441.49 \
  -875.55 -955.93 819.56 \
  991.36 -802.33 367.04 \
  283.03 452.45 -787.10");
  a.MulMatrix(b);
  S21Matrix answer(4, 3);
  answer.Read(
      "-104521.64169999998 -752479.9771 279934.1232 \
  1098483.2587 -283907.12080000003 -106020.54659999997 \
  317712.4667 -1008474.7295	904681.4562 \
  -453505.3218000001 762629.7220999999 -24578.659900000086");
  ASSERT_TRUE(a == answer);

  S21Matrix d(2, 5), e(4, 3);
  int error = 0;
  try {
    d *= e;
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);
}

TEST(MethodsTest, Transpose) {
  S21Matrix a(3, 4);
  a.Read(
      "785.33 -209.76 -434.68 988.00 \
  37.50 805.06 858.46 -43.68 \
  -172.55 784.81 -552.90 943.83");
  a.Transpose();
  S21Matrix answer(4, 3);
  answer.Read(
      "785.33 37.5 -172.55 \
  -209.76 805.06 784.81 \
  -434.68 858.46 -552.9 \
  988 -43.68 943.83");
  ASSERT_TRUE(a == answer);
}

TEST(MethodsTest, CalcComplements) {
  S21Matrix a(4, 4);
  a.Read(
      "-5 8 9 -8 \
  -2 -4 2 8 \
  3 7 9 -1 \
  6 5 0 -1");
  S21Matrix b = a.CalcComplements();
  S21Matrix answer(4, 4);
  answer.Read(
      "-320	420	-200	180 \
  -306	450	-202	414 \
  388	-520	436	-272 \
  -276	760	-452	424");
  ASSERT_TRUE(b == answer);

  S21Matrix c(2, 5);
  int error = 0;
  try {
    c.CalcComplements();
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);
}

TEST(MethodsTest, Determinant) {
  S21Matrix a;
  ASSERT_TRUE(a.Determinant() == 0);

  S21Matrix b(6, 6);
  b.Read(
      "70 -8.6 12.4 -15 20.4 -23 \
  -2457.6 35.4 -38 47.4 -50 61 \
  68.4 -71 84.4 -87 102 -104.6 \
  -114 131.4 -134 153 -155.6 176.2 \
  188.4 -191 214 -216.6 241.2 -243.8 \
  -258 285 -287.6 316.2 -318.8 349");
  EXPECT_DOUBLE_EQ(b.Determinant(), -32152863.375360902);

  S21Matrix c(8, 8);
  c.Read(
      "0 1 2 5 -8 3 -2 6 \
  -7 1 4 -6 -7 -6 -5 -4 \
  0 -1 1 9 5 3 2 -6 \
  4 -7 -7 -6 -2 1 -7 -1 \
  4 -6 4 4 0 9 -5 -3 \
  3 6 4 9 8 3 5 3 \
  0 -4 -6 5 -6 -3 6 5 \
  9 -6 3 3 -7 -8 -3 0");
  EXPECT_DOUBLE_EQ(c.Determinant(), -27007408);

  S21Matrix d(6, 6);
  d.Read(
      "45.23 12.73 -3.44 37.84 -67.23 -43.60 \
  -76.69 -5.23 96.65 35.17 -86.35 6.38 \
  50.22 -14.03 81.52 55.38 -52.04 -64.36 \
  -44.56 96.51 -51.34 -93.88 -29.74 45.77 \
  6.45 -36.80 -41.98 -50.37 -68.41 -1.78 \
  90.14 -82.40 -44.90 59.76 -69.97 -49.37");
  EXPECT_DOUBLE_EQ(d.Determinant(), 150917751763.14868);

  S21Matrix e(4, 4);
  e.Read(
      "-197.2197 -220.4329 31.9360 443.1550 \
  129.4678 417.3718 -168.0046 -7.4547 \
  100.9716 552.0616 170.4274 323.0880 \
  332.7959 -9.7684 563.5200 -607.5236");
  EXPECT_DOUBLE_EQ(e.Determinant(), -10169373428.624538);

  S21Matrix f(2, 2);
  f.Read(
      "788.7471 -915.2059 \
  -3065.5259 462.1727");
  EXPECT_DOUBLE_EQ(f.Determinant(), -2441050.0134586403);
}

TEST(MethodsTest, InverseMatrix) {
  S21Matrix a(5, 5);
  a.Read(
      "162.77 -317.58 -347.17 -706.25 26.03 \
  -978.64 -324.63 -485.67 239.60 -168.63 \
  735.31 11.09 -490.70 -267.46 229.53 \
  -560.85 -426.04 -513.10 -400.32 -649.22 \
  -873.59 -962.66 -7.35 76.45 -649.33");
  S21Matrix b = a.InverseMatrix();
  S21Matrix answer(5, 5);
  answer.Read(
      "-0.00070202368526860252	-0.00076354440333777923	\
  0.00112330812198077790	0.00011700570187169406	0.00045023838060218182 \
  -0.00050299538735191681	-0.00004132787171343412	-0.00071696371546286786	\
  0.00108441215218204453	-0.00134709714625160243 \
  0.00047397501775811813	-0.00075764766757724574	-0.00112488298837683566	\
  -0.00048099995357657276	0.00029904685357929287 \
  -0.00152907189859224766	0.00025659347800487971	0.00112306250994983957	\
  -0.00029033283104271819	0.00055933857786028846 \
  0.00150480210027889549	0.00112730772649603570	-0.00030337799439956326	\
  -0.00179384258973416937	-0.00008618694376677678");
  ASSERT_TRUE(b == answer);

  S21Matrix c(2, 5);
  int error = 0;
  try {
    c.InverseMatrix();
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);

  S21Matrix d;
  error = 0;
  try {
    c.InverseMatrix();
  } catch (exception& e) {
    error = 1;
  }
  ASSERT_TRUE(error == 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
