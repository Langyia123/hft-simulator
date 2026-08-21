cmake_minimum_required(VERSION 3.20) 

project(hft_simulator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hft_simulator
    src/main.cpp
    src/order.cpp
    src/order_book.cpp
)

target_include_directories(hft_simulator PRIVATE include)

#This tells means that this project needs CMake version 3.20 or newer
#The name of the project is hft_simulator
#Compile this project using C++ 23
#Actually use C++ 23 and don't fall back on older versions
#Build an executable called hft_simulator using src/main.cpp
