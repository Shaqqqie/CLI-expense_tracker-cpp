#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

#include "ExpenseTracker.hpp"
#include "Expense.hpp"

void ExpenseTracker::AddExpense()
{
std:
    std::string category{};
    std::cout << "\nEnter Category: ";
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
    std::getline(std::cin, category);

    int AmountInCents{};
    while (true)
    {
        std::cout << "Enter amount in cents: ";

        if (std::cin >> AmountInCents)
        {
            break;
        }

        std::cout << "Input must be an integer greater than 0.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
    std::string description{};
    std::cout << "Enter a description: ";
    std::cin >> description;

    Expense expense(category, AmountInCents, description);
    expenses.push_back(expense);
}

void ExpenseTracker::ViewExpenses() const
{
    for (const auto &expense : expenses)
    {
        std::cout << expense << "\n";
    }
}

void ExpenseTracker::ShowTotal() const
{
    unsigned int total{};
    for (const auto &expense : expenses)
    {
        total += expense.GetAmount();
    }

    std::cout << "Total expenses: $" << total / 100 << "." << std::setfill('0') << std::setw(2) << total % 100 << "\n";
}

void ExpenseTracker::SaveExpenses() const
{
    std::ofstream file{"data/expenses.txt"};

    if (!file)
    {
        std::cout << "Could not open file\n";
        return;
    }

    for (const auto &expense : expenses)
    {
        file << expense.GetCategory() << "|" << expense.GetAmount() << "|" << expense.GetDescription() << "\n";
    }
}