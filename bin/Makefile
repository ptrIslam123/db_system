compilMain:
	clang++ -g -c ../main.cpp

compil:
	clang++ -g -c ../interpret/*.cpp
	clang++ -g -c ../db_kernel/*.cpp
	clang++ -g -c ../tools/*.cpp
	clang++ -g -c ../*.cpp

link:
	clang++ *.o -o main

run:
	./main

clear:
	rm *.o

delete:
	rm *