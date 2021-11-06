cmake_minimum_required(VERSION 3.20)
project(bigproject C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fexec-charset=GBK")

add_executable(bigproject main.c paint.h pageMain.h utils.h funtionList.h pageOne.h)
