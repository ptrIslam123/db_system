compilFstream:
	clang++ -g -c ../file_stream.cpp 

compilToken:
	clang++ -g -c ../token.cpp

compilMethods:
	clang++ -g -c ../methods.cpp

compilDBContoller:
	clang++ -g -c ../db_controller.cpp

compilDB_kernel:
	clang++ -g -c ../db_kernel.cpp

compil:
	clang++ -g -c ../*.cpp

compilTokenGrammar:
	clang++ -g -c ../tokenize_grammar.cpp

compilTest:
	clang++ -g -c ../test/*.cpp

compilMain:
	clang++ -g -c ../main.cpp

link:
	clang++ *.o -o main

run:
	./main

buildTokenGrammar:
	make compilTokenGrammar
	make link

buildMain:
	make compilMain
	make link


build:
	make compil
	make link

debug:
	gdb main

clear:
	rm *.o
