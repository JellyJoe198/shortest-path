cmake_minimum_required(VERSION 3.20)
project(Final_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories("C:/mingw/include")
include_directories("C:/mingw64/include")
include_directories("C:/mingw64/mingw64/include")
include_directories("C:/mingw64/x86_64-w64-mingw32/include")

add_executable(Final_Project main.cpp
        class/point.hpp
        #class/World.h
        class/World.cpp
        class/coord.hpp
        #[[function/hue.cpp]]
        )

target_link_directories(Final_Project PUBLIC "C:/mingw/lib")
target_link_directories(Final_Project PUBLIC "C:/mingw64/lib")
target_link_directories(Final_Project PUBLIC "C:/mingw64/mingw64/lib")
target_link_directories(Final_Project PUBLIC "C:/mingw64/x86_64-w64-mingw32/lib")
#target_link_directories(Final_Project PUBLIC point.inl)

target_link_libraries(Final_Project sfml-graphics sfml-system sfml-window sfml-main)
