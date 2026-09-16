cmake_minimum_required(VERSION 3.20)

project(expense_tracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(expense_tracker
    src/main.cpp
    src/Expense.cpp
    src/ExpenseTracker.cpp
    src/MoneyUtils.cpp
)

target_compile_options(expense_tracker PRIVATE
    -Wall
    -Wextra
    -Wpedantic    
)

target_include_directories(expense_tracker PRIVATE include)