cmake_minimum_required(VERSION 3.21)
project(Project1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project1 main.c register.c datastructure.h interface.c interface.h utils.c utils.h register.h login.c login.h user.c user.h book_management.c admin.c admin.h)
