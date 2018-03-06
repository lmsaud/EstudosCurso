cmake_minimum_required(VERSION 3.9)
project(untitled1 C)

set(CMAKE_C_STANDARD 99)

set(EstudosCurso main.c)
add_executable(EstudosCurso main.c)
target_link_libraries(EstudosCurso mysqlclient)

include_directories(/usr/include/mysql/)

link_directories(/usr/include/mysql/)