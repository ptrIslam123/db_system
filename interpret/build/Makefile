compilToken:
	clang++ -g -c ../../db_kernel/token.cpp

compilMethodsDB:
	clang -g -c ../../db_kernel/methods.cpp


compilDBContoller:
	clang++ -g -c ../../db_kernel/db_controller.cpp

compilDBKernel:
	clang++ -g -c ../../db_kernel/db_kernel.cpp


compilTokenGrammar:
	clang++ -g -c ../../db_kernel/tokenize_grammar.cpp

compilFstream:
	clang++ -g -c ../../db_kernel/file_stream.cpp



compilTrigersAdd:
	clang++ -g -c ../../db_kernel/triger_add.cpp

compilTrigersRemove:
	clang++ -g -c ../../db_kernel/triger_remove.cpp


compilTrigersInsert:
	clang++ -g -c ../../db_kernel/triger_insert.cpp

compilTrigersDropTable:
	clang++ -g -c ../../db_kernel/triger_drop_table.cpp

compilTrigers:
	make compilTrigersAdd
	make compilTrigersInsert
	make compilTrigersRemove
	make compilTrigersDropTable


compilEvent:
	clang++ -g -c ../../db_kernel/event.cpp

compilDB_API:
	make compilDBContoller
	make compilToken
	make compilTokenGrammar
	make compilFstream
	make compilMethodsDB
	make compilDBKernel

compil:
	clang++ -g -c ../*.cpp

compilMain:
	clang++ -g -c ../main.cpp

compilListTriggers:
	clang++ -g -c ../list_triggers.cpp

compilTriggerNode:
	clang++ -g -c ../trigger_node.cpp

compilTriggerOperators:
	clang++ -g -c ../trigger_operators.cpp

compilLexeme:
	clang++ -g -c ../lexeme.cpp

compilBaseParse_API:
	clang++ -g -c ../base_parse_api.cpp

compilOperators:
	clang++ -g -c ../operators.cpp

compilAtomicOperators:
	clang++ -g -c ../atomic_operators.cpp

compilResponse:
	clang++ -g -c ../response_data.cpp

compilSysFunctions:
	clang++ -g -c ../sys_functions.cpp

compilParser:
	clang++ -g -c ../parser.cpp

compilTransaction:
	clang++ -g -c ../transaction.cpp

compilSharedOprt:
	clang++ -g -c ../shared_oprt_funcs.cpp

compilOptionParse:
	clang++ -g -c ../option_parse.cpp

compilCommand:
	clang++ -g -c ../command.cpp

compilArgsData:
	clang++ -g -c ../args_data.cpp

compilShell:
	clang++ -g -c ../shell.cpp

link:
	clang++ *.o -o main


build:
	make compil
	make link

buildMain:
	make compilMain
	make link

run:
	./main

kdebug:
	kdbg main

debug:
	gdb main

clear:
	rm *.o
