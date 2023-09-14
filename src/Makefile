CFLAGS = -std=c++17
TFLAGS = -lgtest -lgmock -pthread
SOURCE = constructors.cpp mutators.cpp operators.cpp methods.cpp utils.cpp
.PHONY: test

all: clean s21_matrix_oop.a test

clean:
	rm -f *.o *.a
	rm -f ./a.out
	rm -rf ./tests/*.o ./tests/*.a ./tests/tests
	rm -rf VALGRIND.txt

test:
	g++ tests/tests.cpp $(SOURCE) -o tests/tests $(TFLAGS)
	./tests/tests

s21_matrix_oop.a:
	g++ $(CFLAGS) -c $(SOURCE)
	ar rcs s21_matrix_oop.a $(OBJ)
	ranlib s21_matrix_oop.a
	rm -f *.o

style:
	cppcheck --language=c++ *.cpp *.h
	cp ../materials/linters/.clang-format ./
#clang-format -i *.cpp *.h tests/*.cpp
	clang-format -n *.cpp *.h tests/*.cpp
	rm -f ./.clang-format
