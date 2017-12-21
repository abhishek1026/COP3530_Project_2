cmake_minimum_required(VERSION 3.8)
project(COP3530_Project_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AVL.h BSTROOT.h BSTLEAF.h BSTRAND.h)
add_executable(COP3530_Project_2 ${SOURCE_FILES} main.cpp AVL.h BSTROOT.h BSTLEAF.h BSTRAND.h)