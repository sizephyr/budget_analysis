cmake_minimum_required(VERSION 3.26)
project(crud_class_test)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

add_executable(crud_class_test ../../src/crud.cxx src/main.cpp)
TARGET_LINK_LIBRARIES(crud_class_test)
