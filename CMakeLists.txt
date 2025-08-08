cmake_minimum_required(VERSION 3.26)
project(MAH)

set(CMAKE_CXX_STANDARD 17)

add_executable(MAH main.cpp
        BookNode.cpp
        Book.cpp
        Admin.cpp
        Filling.cpp
        HashTables.cpp
        User.cpp
        Admin_list.h
        Admin_list.cpp
        Functions.h)
