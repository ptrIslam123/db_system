compilMain:
	clang++ -Wall -g -c ../main.cpp

compil:
	clang++ -Wall -g -c ../interpret/*.cpp
	clang++ -Wall -g -c ../db_kernel/*.cpp
	clang++ -Wall -g -c ../tools/*.cpp
	clang++ -Wall -g -c ../*.cpp

link:
	clang++ *.o -o main

run:
	./main

clear:
	rm *.o

delete:
	rm *
