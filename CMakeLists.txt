cmake_minimum_required(VERSION 3.24)
project(budget_analysis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)
#TARGET_LINK_LIBRARIES(budget_analysis ${PQXX_LIB} ${PQ_LIB})

add_executable(budget_analysis src/main.cpp)
TARGET_LINK_LIBRARIES(budget_analysis ${PQXX_LIB} ${PQ_LIB})
