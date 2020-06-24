cmake_minimum_required(VERSION 3.16)
project(DeadlockRecovery C)

set(CMAKE_C_STANDARD 99)

add_executable(DeadlockRecovery main.c main.h src/deadlockRecovery.c src/deadlockRecovery.h src/file.c src/file.h)