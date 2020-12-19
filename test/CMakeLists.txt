cmake_minimum_required(VERSION 3.2)

project(test)


add_definitions( -Wall)

set(CPPS 
    main.cpp)

add_executable(main ${CPPS})
message("BULD!")