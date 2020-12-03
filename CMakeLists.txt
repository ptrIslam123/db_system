cmake_minimum_required(VERSION 2.8)

project(dbsystem)

file(GLOB CPPS "*.cpp" "db_kernel/*.cpp" "interpret/*.cpp" "tools/*.cpp")

add_executable(main ${CPPS})

message("BUILD PROJECT")