cmake_minimum_required(VERSION 3.20)

project(expense_tracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_library(expense_tracker_lib
    src/Expense.cpp
    src/ExpenseTracker.cpp
    src/MoneyUtils.cpp
)

target_include_directories(expense_tracker_lib PUBLIC include)

target_compile_options(expense_tracker_lib PRIVATE
    -Wall
    -Wextra
    -Wpedantic    
)

add_executable(expense_tracker
    src/main.cpp
)

target_link_libraries(expense_tracker PRIVATE expense_tracker_lib)

target_compile_options(expense_tracker PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(expense_tracker_tests
    tests/MoneyUtilsTests.cpp
)

target_link_libraries(expense_tracker_tests PRIVATE
    expense_tracker_lib
    Catch2::Catch2WithMain
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(expense_tracker_tests)
