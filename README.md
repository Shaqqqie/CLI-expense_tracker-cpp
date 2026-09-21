# CLI Expense Tracker

A command-line expense tracking application written in C++.

## Features

- Add expenses with a category, amount, and description
- View all expenses
- Filter expenses by category
- Edit existing expenses
- Delete expenses
- Sort expenses by amount or category
- Display expense summaries
- Save expenses to a file
- Load saved expenses when the application starts
- Input validation and malformed-data handling

## Technologies

- C++20
- CMake
- Catch2
- CTest
- clang-tidy
- cppcheck
- AddressSanitizer
- GCC and Clang

## Project Structure

```
expense-tracker-cpp/
├── include/
│   ├── Expense.hpp
│   ├── ExpenseTracker.hpp
│   ├── InputUtils.hpp
│   └── MoneyUtils.hpp
├── src/
│   ├── Expense.cpp
│   ├── ExpenseTracker.cpp
│   ├── InputUtils.cpp
│   ├── MoneyUtils.cpp
│   └── main.cpp
├── tests/
│   ├── ExpenseTests.cpp
│   ├── ExpenseTrackerTests.cpp
│   └── MoneyUtilsTests.cpp
├── data/
│   └── expenses.txt
├── CMakeLists.txt
└── README.md
```

## Building

From the project root:

```
cmake -S . -B build
cmake --build build
```

Run the application:
```
./build/expense_tracker
```

## Testing

The project uses Catch2 with CTest.

Run the test suite with:

```
ctest --test-dir build --output-on-failure
```

## Code Quality

The project uses compiler warnings and static-analysis tools to catch potential
problems and improve code quality.

Compiler warnings:
```
-Wall -Wextra -Wpedantic
```

Static analysis:
```
cppcheck --enable=all --std=c++20 --suppress=missingIncludeSystem -I include src/ include/
```

clang-tidy is integrated into the CMake configuration.

The project has also been tested with AddressSanitizer and multiple compilers.

## What I Learned

This project was built as part of my C++ learning process. It gave me practical experience with:

- Classes and encapsulation
- Const correctness
- References and value semantics
- `std::vector`
- STL algorithms and ranges
- Lambda expressions
- `enum class`
- Input validation
- File I/O and persistence
- String streams
- Exception handling
- Operator overloading
- Separating application logic from CLI/input logic
- Unit testing with Catch2
- CMake targets and libraries
- Static analysis and sanitizers