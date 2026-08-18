cmake_minimum_required(VERSION 3.16)
project(AlgorithmsAndDataStructuresCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sorting_algorithms
    assignments/01-sorting-algorithms/main.cpp)

add_executable(topological_sort
    assignments/02-topological-sort/main.cpp)

add_executable(kruskal_mst
    assignments/03-kruskal-mst/main.cpp)

add_executable(set_of_integers
    assignments/04-set-of-integers/main.cpp)

add_executable(employee_file_processing
    assignments/05-employee-file-processing/main.cpp)
