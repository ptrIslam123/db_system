compilTooslFiles:
	clang++ -g -c ../../tools/files.cpp

compilInterpretAPI:
	clang++ -g -c ../../interpret/*.cpp

compilCommand:
	clang++ -g -c ../../interpret/command.cpp

compilParser:
	clang++ -g -c ../../interpret/parser.cpp

compilBaseParseApi:
	clang++ -g -c ../../interpret/base_parse_api.cpp

compilTriggerNode:
	clang++ -g -c ../../interpret/trigger_node.cpp

compilSysError:
	clang++ -g -c ../../interpret/sys_error.cpp

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

compilTrigerAdd:
	clang++ -g -c ../triger_add.cpp

compilTrigerREmove:
	clang++ -g -c ../triger_remove.cpp

compilTrigerInsert:
	clang++ -g -c ../triger_insert.cpp

compilTrigerDropTable:
	clang++ -g -c ../triger_drop_table.cpp

compilEvent:
	clang++ -g -c ../event.cpp

compilToolsLoger:
	clang++ -g -c ../../tools/loger.cpp

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
