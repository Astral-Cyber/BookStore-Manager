cmake_minimum_required(VERSION 3.19)
project(BookStore_Manager)

set(CMAKE_CXX_STANDARD 14)

add_executable(BookStore_Manager
        main.cpp shelf.cpp book.h)
