cmake_minimum_required(VERSION 3.30)
project(RDPCalculator)

set(CMAKE_CXX_STANDARD 26)

add_executable(RDPCalculator
        #main.cpp
        token.cpp
        token.h
        constants.h
        Variable.h
        SymbolTable.cpp
        SymbolTable.h
        utility.h
        enums.h
        Calculator.cpp
        Calculator.h
        runner.cpp
)

find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests tests/test.cpp token.cpp
        token.h
        constants.h
        Variable.h
        SymbolTable.cpp
        SymbolTable.h
        utility.h
        enums.h
        Calculator.cpp
        Calculator.h)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# These tests need their own main
# add_executable(custom-main-tests test.cpp test-main.cpp
        #tests/test.cpp)
# target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)


