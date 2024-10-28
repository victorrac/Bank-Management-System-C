cmake_minimum_required(VERSION 3.27)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled1
        main.c
        header.h
        AccountOperations.c
        Database.c
        HelpFunctions.c
        Login+FirstAccount.c
        Menu.c
)

