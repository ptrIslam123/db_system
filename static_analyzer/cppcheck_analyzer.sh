#!/bin/bash


run_db_kernel(){
	echo "RUN_ANALYZE {../db_kernel/*.cpp}:"
	echo ""
	cppcheck ../db_kernel/
}

run_tools(){
	echo "RUN_ANALYZE {../tools/*.cpp}:"
	echo ""
	cppcheck ../tools/
}

run_interpret(){
	echo "RUN_ANALYZE {../interpret/*.cpp}:"
	echo ""
	cppcheck ../interpret/
}

run_all(){
	run_db_kernel
	run_interpret
	run_tools
}

run_all
echo "#_END_"