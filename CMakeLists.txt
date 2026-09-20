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
    src/InputUtils.cpp
)

set_target_properties(expense_tracker_lib PROPERTIES
    CXX_CLANG_TIDY
    "clang-tidy;-checks=bugprone-*,performance-*,modernize-*,-modernize-use-trailing-return-type"
)

target_include_directories(expense_tracker_lib PUBLIC include)

if (MSVC)
    set(PROJECT_WARNINGS /W4)
else ()
    set(PROJECT_WARNINGS -Wall -Wextra -Wpedantic)
endif()

target_compile_options(expense_tracker_lib PRIVATE ${PROJECT_WARNINGS})

add_executable(expense_tracker
    src/main.cpp
)

set_target_properties(expense_tracker PROPERTIES
    CXX_CLANG_TIDY
    "clang-tidy;-checks=bugprone-*,performance-*,modernize-*,-modernize-use-trailing-return-type"
)

target_link_libraries(expense_tracker PRIVATE expense_tracker_lib)

target_compile_options(expense_tracker PRIVATE ${PROJECT_WARNINGS})


add_executable(expense_tracker_tests
    tests/MoneyUtilsTests.cpp
    tests/ExpenseTests.cpp
    tests/ExpenseTrackerTests.cpp
)

target_link_libraries(expense_tracker_tests PRIVATE
    expense_tracker_lib
    Catch2::Catch2WithMain
)

target_compile_options(expense_tracker_tests PRIVATE ${PROJECT_WARNINGS})


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(expense_tracker_tests)
