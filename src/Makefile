CC=gcc
CFLAGS=-Wall -Werror -Wextra
LIBS=
OPEN=

OS=$(shell uname)
ifeq ($(OS), Linux)
	LIBS=-lcheck -lpthread -lrt -lm -lsubunit 
	OPEN=xdg-open
else
    LIBS=-lcheck -lm
	OPEN=open
endif

all: s21_matrix.a test

s21_matrix.a:
	$(CC) $(CFLAGS) -c s21_matrix.c
	ar rcs libs21_matrix.a s21_matrix.o
	ranlib libs21_matrix.a
	cp libs21_matrix.a s21_matrix.a

test:
	$(CC) $(CFLAGS) s21_matrix_test.c s21_matrix.c -o s21_test.out $(LIBS)
	make run

gcov_report:
	$(CC) $(CFLAGS) -o s21_test.out --coverage s21_matrix.c s21_matrix_test.c $(LIBS)
	make run
	lcov -t "s21_test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN) report/index.html

clean:
	rm -rf *.o *.a *.out *.gcda *.gcno *.info *.dSYM *.info report

miniverter:
	sudo chmod +x ../materials/build/./run.sh
	sudo ../materials/build/./run.sh

run:
	./s21_test.out

check: 
	cp ../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --quiet  --extension=c *.c *.h
	cppcheck --quiet --enable=all --suppress=missingIncludeSystem *.c *.h

leaks: clean test
	CK_FORK=no leaks --atExit --  ./s21_test.out

valgrind:
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./s21_test.out
	
