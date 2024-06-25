cmake_minimum_required(VERSION 3.28)
project(wuziqi)

set(CMAKE_CXX_STANDARD 17)
include_directories(E:/learn/code/C++/wuziqi/EasyX/include)
link_directories(E:/learn/code/C++/wuziqi/EasyX/lib64)
link_libraries(libeasyx.a)
link_libraries(easyx)

add_executable(wuziqi main.cpp
        Man.cpp
        Man.h
        Chess.cpp
        Chess.h
        ChessGame.cpp
        ChessGame.h)
