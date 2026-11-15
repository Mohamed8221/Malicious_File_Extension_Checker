cmake_minimum_required(VERSION 3.10)
project(MaliciousFileExtensionChecker CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(extension_checker main.cpp)
