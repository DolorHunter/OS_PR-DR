cmake_minimum_required(VERSION 3.16)
project(PagesReplacement C)

set(CMAKE_C_STANDARD 99)

add_executable(PagesReplacement main.c main.h src/timer.c src/timer.h src/pagesReplacement.c src/pagesReplacement.h src/file.c src/file.h)