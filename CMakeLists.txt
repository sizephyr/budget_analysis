cmake_minimum_required(VERSION 3.26)
project(budget_analysis)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_executable(budget_analysis src/crud.cxx src/main.cpp)
TARGET_LINK_LIBRARIES(budget_analysis ${PQXX_LIB} ${PQ_LIB})
