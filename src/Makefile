TARGET = s21_string.a
GCC = gcc -Wall -Werror -Wextra -std=c11 -pedantic -g 
LC=-lcheck
GCOV=-fprofile-arcs -ftest-coverage
UNIX = -lsubunit -lrt -lpthread -lm -D_GNU_SOURCE
OS=$(shell uname -s)

ifeq ($(OS),Darwin)
  	OPEN = open
	LC = -lcheck
	VALGRIND = open -a 'Docker' && cd .. && cd materials/build/valgrind && bash run.sh
endif
ifeq ($(OS),Linux)
	OPEN = xdg-open
	LC = -lcheck -lsubunit -lrt -lpthread -lm -D_GNU_SOURCE
	VALGRIND = make s21_string.a && cd tests && gcc -g s21_string_test.c ../s21_string.a -o test -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit && valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test && cd ..
endif

TESTN = test
TESTS = tests/*.c
CLANG = clang-format -style=Google

all: $(TARGET)

$(TARGET):
	$(GCC) -c s21_*.c
	ar rc $(TARGET) s21_*.o
	ranlib $(TARGET)

style:
	$(CLANG) -n *.c *.h
	$(CLANG) -i *.c *.h
	$(CLANG) -n */*.c *.h
	$(CLANG) -i */*.c *.h

test: clean $(TARGET) 
	$(GCC) -o $(TESTN) $(LC) $(TESTS) $(TARGET) ./*.c -lcheck --coverage
	./test

clean_test:
	rm -rf *.gcda *.gcno $(TESTN)

clean:
	rm -rf *.o *.a *.gcda *.gcno
	rm -rf *.info *.gcov *.html 
	rm -rf *.dSYM *.info *.log
	rm -rf test report .gitignore .gitkeep


gcov_report: clean
	$(GCC) $(GCOV) s21_*.c  $(TESTS) -o $(TESTN) $(LC)
	./$(TESTN)
	lcov -t "test" -o $(TESTN).info -c -d .
	genhtml -o report $(TESTN).info
	$(OPEN) ./report/index.html
	make clean_test


leaks: test
	CK_FORK=no leaks -atExit -- ./$(TESTN) $t > testleaks.log
	$(OPEN) testleaks.log
	make clean

valgrind:
	$(VALGRIND)