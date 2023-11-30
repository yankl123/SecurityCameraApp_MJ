project(sqlite)

cmake_minimum_required(VERSION 3.10)

add_library(sqlite STATIC
    sqlite3.c
    #header files
    sqlite3.h
)




