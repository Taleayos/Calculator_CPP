FLAGS = -Wall -Werror -Wextra -std=c++17

all: gcov_report install

install:
	cd View && qmake && make && make clean
	cp -r View/Calc.app ~/Desktop

uninstall:
	rm -rf View/Calc.app 
	rm -rf ~/Desktop/Calc.app
	rm -rf View/Makefile

clean:
	rm -rf *.o *.a *.out *.info report test.dSYM *.gcno *.gcda test html latex
dvi:
	doxygen Doxyfile
	open ./html/index.html

dist: install
	mkdir archiv
	cp -r *.c *.h Makefile SmartCalc/ archiv
	tar -cvzf SmartCalc.tar.gz archiv
	rm -rf archiv

test: clean
	g++ $(FLAGS) Tests/test.cc Logic/model.cc -lgtest -o test -lstdc++
	./test

gcov_report: clean
	g++ $(FLAGS) --coverage Tests/test.cc Logic/model.cc -o test -lgtest 
	./test
	lcov -t "test" -o test.info -c -d . --no-external
	genhtml -o report test.info
	open report/index.html

style:
	clang-format -n Logic/*.cc Logic/*.h Tests/test.cc

leaks: test
	leaks -atExit -- ./test