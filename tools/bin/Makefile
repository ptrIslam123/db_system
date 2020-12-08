compil:
	clang++ -g -c ../*.cpp

compilMain:
	clang++ -g -c ../main.cpp

compilFiles:
	clang++ -g -c ../files.cpp

compilLoger:
	clang++ -g -c ../loger.cpp

link:
	clang++ *.o -o main

buildMain:
	make compilMain
	make link


build:
	make compil
	make link

run:
	./main


clear:
	rm *.o

