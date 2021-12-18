cmake_minimum_required(VERSION 3.20)
project(bigproject C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fexec-charset=GBK")

add_executable(bigproject main.c paint.c pageMain.c utils.c functionList.h pageGuessNumber.c point.c headList.h pageGluttonousSnake.c pageList.h global.h fileUtils.c lib/sqlite3.c lib/sqlite3.h pageTetris.c sqlUtils.c sqlUtils.h user.c user.h point.h)