cmake_minimum_required(VERSION 3.29)
project(OS_Lab C)

set(CMAKE_C_STANDARD 11)

add_executable(FCFS fcfs_myself.c)
add_executable(SJF sjf_from_web.c)
add_executable(SRJF SRJF_from_web.c)
add_executable(Round_Robin round_robin_myself.c)
add_executable(Round_Robin_web round_robin_web.c)
