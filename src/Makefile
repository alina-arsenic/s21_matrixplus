SOURCE=constructors.cpp mutators.cpp operators.cpp methods.cpp utils.cpp
.PHONY: test

all:
	g++ main.cpp $(SOURCE) -o app; ./app

clean:

test:
	g++ test.cpp $(SOURCE) -o test -lgtest -lgmock -pthread
	./test

s21_matrix_oop.a:
