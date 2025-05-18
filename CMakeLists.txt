cmake_minimum_required(VERSION 3.14)

# Project name and version
project(Accumulate VERSION 1.0
	          DESCRIPTION "Accumulation of a sum of many values"
		      LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add the executable
add_executable(accumulate src/main.cpp)
