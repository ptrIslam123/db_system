cmake_minimum_required(VERSION 2.8)

project(dbsystem)

file(GLOB CPPS  "*.cpp" "db_kernel/*.cpp"
                "interpret/*.cpp" 
                "tools/*.cpp"
                "vcs/*.cpp")
                

add_definitions( -Wall -g )

add_executable(dbs ${CPPS})

message("BUILD PROJECT")
