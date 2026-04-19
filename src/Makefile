CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -lcheck -lm -lpthread -lsubunit
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

.PHONY: all test gcov_report clean

all: s21_matrix.a

s21_matrix.a: extra_function.o s21_matrix.o 
	# Создать статическую библиотеку с помощью archiver
	ar rcs s21_matrix.a extra_function.o s21_matrix.o 

extra_function.o: extra_function.c 
	$(CC) $(CFLAGS) -c extra_function.c -o extra_function.o

s21_matrix.o: s21_matrix.c 
	$(CC) $(CFLAGS) -c s21_matrix.c -o s21_matrix.o

test: clean s21_matrix.a matrix_test.o
	# Линковать тесты с библиотекой в исполняемый файл
	$(CC) $(CFLAGS) -o test matrix_test.o s21_matrix.a $(LDFLAGS) 
	# Запустить тесты
	./test
#gcc -Wall -Wextra -Werror s21_matrix.c -lcheck -lm -lsubunit -o test
matrix_test.o: matrix_test.c
	$(CC) $(CFLAGS) -c matrix_test.c -o matrix_test.o

valgrind: test
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

v: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=log.txt ./test
gcov_report: clean
	@echo "Generating coverage report..."
	
	# Компилируем с флагами покрытия
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o test extra_function.c s21_matrix.c matrix_test.c $(LDFLAGS)
	
	# Запускаем тесты
	./test
	
	# Создаем директорию для отчета
	mkdir -p report
	
	# Генерируем HTML отчет с помощью gcovr
	gcovr -r . --html --html-details -o report/index.html
	
	@echo "HTML report generated in ./report/index.html"

show:
	xdg-open report/index.html

clean:
	rm -f *.o *a test *gcno *info
	rm -rf report