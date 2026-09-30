# CLI Expense Tracker

A command-line expense tracking application built with modern C++.

The application allows users to record, manage, sort, and summarize expenses while storing expense data between program runs.

This project focuses on building a complete command-line application with input validation, file persistence, automated testing, and separation of responsibilities.

## Features

- Add expenses
- View recorded expenses
- Edit existing expenses
- Delete expenses
- Calculate the total amount spent
- Sort expenses by amount
- Sort expenses by category
- Filter expenses by category
- Display expense summaries
- Persistent expense storage
- Input validation
- Currency formatting
- Automated tests

### Sorting

Expenses can be sorted in multiple ways:

- Amount: low to high
- Amount: high to low
- Category: A to Z
- Category: Z to A

## Application Menu

```text id="al29md"
Expense tracker
1. Add expense
2. View expenses
3. Show total
4. Delete expense
5. Edit expense
6. Sort expenses
7. Show summary
8. Exit
Choose an option:
```

## Technologies

- **C++20**
- **CMake**
- **Catch2**
- **GitHub Actions**
- GCC / Clang
- clang-tidy
- AddressSanitizer
- UndefinedBehaviorSanitizer

## Project Structure

```text id="j9gm0e"
expense-tracker-cpp/
├── data/
│   └── expenses.txt
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
├── CMakeLists.txt
└── README.md
```

The application is divided into several components:

- `Expense` represents an individual expense and validates its data.
- `ExpenseTracker` manages the collection of expenses and provides operations such as adding, editing, deleting, filtering, sorting, and calculating totals.
- `InputUtils` handles command-line input and input validation.
- `MoneyUtils` provides money-related formatting functionality.
- `main.cpp` provides the interactive command-line interface.

## Expense Data

Each expense contains:

- Category
- Amount
- Description

Amounts are stored internally in cents rather than floating-point values.

For example:

```text id="b4u8fg"
€12.50 -> 1250 cents
```

Using integer cents avoids common floating-point precision problems when representing monetary values.

## Building the Project

### Requirements

- A C++20-compatible compiler
- CMake
- Git

### Clone

```bash id="5tjjqk"
git clone https://github.com/Shaqqqie/CLI-expense_tracker-cpp.git
cd CLI-expense_tracker-cpp
```

### Configure

```bash id="qrsbzj"
cmake -S . -B build
```

### Build

```bash id="43ks6x"
cmake --build build
```

## Running

After building:

```bash id="y05ozf"
./build/expense_tracker
```

The application provides an interactive menu for managing expenses.

## Persistent Storage

Expenses are stored in:

```text id="drdzb4"
data/expenses.txt
```

Saved expenses can be loaded again when the application is started later.

This allows expense data to persist between program runs.

## Running the Tests

The project uses Catch2 for automated testing.

```bash id="2vrce9"
ctest --test-dir build --output-on-failure
```

The test suite covers functionality including:

- Expense construction
- Expense validation
- Updating expense data
- Adding expenses
- Deleting expenses
- Editing expenses
- Invalid indices
- Invalid amounts
- Invalid categories
- Total calculations
- Empty tracker behavior
- Filtering by category
- Sorting by amount
- Sorting by category
- Currency formatting

## Validation

The application validates user and expense data to prevent invalid state.

Examples include:

- Categories cannot be empty.
- Expense amounts must be greater than zero.
- Invalid expense indices are rejected.
- Invalid edits are rejected.

## Code Quality

The project uses several tools and compiler features to help detect problems during development:

- Compiler warnings
- clang-tidy
- AddressSanitizer
- UndefinedBehaviorSanitizer
- Automated unit tests
- Continuous integration with GitHub Actions

These tools help catch memory errors, undefined behavior, suspicious code, and regressions.

## What I Practiced

This project helped me gain experience with:

- Object-oriented C++
- Application structure
- Separation of responsibilities
- `std::vector`
- File I/O
- Data persistence
- Input validation
- Exception handling
- Sorting and filtering
- Lambda expressions
- Money representation
- String formatting
- Automated testing with Catch2
- CMake
- Static analysis
- Sanitizers
- Continuous integration
- Git and GitHub workflow

## Design Decisions

### Store Money as Integer Cents

Expense amounts are represented as integer cents instead of floating-point numbers.

This makes monetary calculations predictable and avoids floating-point precision issues.

### Separate Input from Business Logic

Input handling is separated from the expense-management logic.

This keeps `ExpenseTracker` focused on managing expenses and makes the core functionality easier to test independently from the command-line interface.

### Automated Testing

Core functionality is tested independently of the user interface.

This allows behavior such as adding, deleting, editing, filtering, sorting, and calculating totals to be verified without manually interacting with the application.

## Future Improvements

Possible future improvements include:

- Expense dates
- Monthly and yearly summaries
- Budget limits
- Additional filtering options
- CSV or JSON export
- Improved command-line interface

## Purpose

This project was built as part of my C++ learning journey to move from small programming exercises toward complete applications.

The focus was not only on implementing features, but also on structuring the code, validating data, persisting information, writing automated tests, and using development tools that help maintain code quality.