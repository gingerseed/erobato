cmake_minimum_required(VERSION 3.30)
project(erobato C)

set(CMAKE_C_STANDARD 11)

add_executable(erobato main.c person.h person.c strops.h strops.c
		data.h
		data.c
		rnd.h
		rnd.c)
