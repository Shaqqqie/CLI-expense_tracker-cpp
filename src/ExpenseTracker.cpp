#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>

#include "ExpenseTracker.hpp"
#include "Expense.hpp"

void ExpenseTracker::AddExpense()
{
    std::string category{};
    std::cout << "\nEnter Category: ";
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
    std::getline(std::cin, category);

    int AmountInCents{GetValidAmount()};

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
    std::string description{};
    std::cout << "Enter a description: ";
    std::getline(std::cin, description);

    Expense expense(category, AmountInCents, description);
    expenses.push_back(expense);
}

void ExpenseTracker::ViewExpenses() const
{
    std::cout << "\n";
    for (std::size_t i{0}; i < expenses.size(); ++i)
    {
        std::cout << i + 1 << ". " << expenses.at(i) << "\n";
    }
    std::cout << "\n";
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

void ExpenseTracker::LoadExpenses()
{
    std::ifstream file{"data/expenses.txt"};

    if (!file)
    {
        std::cerr << "Could not open file.\n";
        return;
    }

    std::string line{};
    while (std::getline(file, line))
    {
        std::istringstream stream{line};

        std::string category{};
        std::getline(stream, category, '|');

        std::string amount{};
        std::getline(stream, amount, '|');

        std::string description{};
        std::getline(stream, description);

        int AmountInCents{std::stoi(amount)};

        Expense expense(category, AmountInCents, description);
        expenses.push_back(expense);
    }
}

void ExpenseTracker::DeleteExpense()
{
    if (expenses.empty())
    {
        std::cout << "There are no expenses to be deleted.\n";
        return;
    }
    ViewExpenses();
    int input{};
    while (true)
    {
        std::cout << "Choose expense to delete(number): ";
        if (std::cin >> input && input > 0 && input <= static_cast<int>(expenses.size()))
        {
            break;
        }

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
    }

    expenses.erase(expenses.begin() + (input - 1));
}

void ExpenseTracker::EditExpense()
{
    if (expenses.empty())
    {
        std::cout << "There are no expenses to edit.\n";
        return;
    }

    ViewExpenses();
    int input{};
    while (true)
    {
        std::cout << "Choose expense to edit(number): ";

        if (std::cin >> input && input > 0 && input <= static_cast<int>(expenses.size()))
        {
            break;
        }

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
    }

    Expense &expense = expenses.at(input - 1);
    int edit{};
    while (true)
    {
        std::cout << "What would you like to edit?\n";
        std::cout << "1. Category\n";
        std::cout << "2. Amount\n";
        std::cout << "3. Description\n";
        std::cout << "4. Cancel\n";
        std::cout << "Choice: ";

        if (std::cin >> edit && edit > 0 && edit <= 4)
        {
            break;
        }

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
    }

    switch (edit)
    {
    case 1:
    {
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
        std::string NewCategory{};
        std::cout << "Enter New Category: ";
        std::getline(std::cin, NewCategory);
        expense.SetCategory(NewCategory);
        std::cout << "Edit successful.\n";
        break;
    }
    case 2:
    {
        int AmountInCents{GetValidAmount()};
        expense.SetAmountInCents(AmountInCents);
        std::cout << "Edit successful.\n";
        break;
    }
    case 3:
    {
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
        std::string NewDescription{};
        std::cout << "Enter New Description: ";
        std::getline(std::cin, NewDescription);
        expense.SetDescription(NewDescription);
        std::cout << "Edit successful.\n";
        break;
    }
    case 4:
        break;
    }
}

int ExpenseTracker::GetValidAmount()
{
    int AmountInCents{};

    while(true)
    {
        std::cout << "Enter amount in cents: ";

        if(std::cin >> AmountInCents && AmountInCents > 0)
        {
            break;
        }

        std::cout << "Amount must be an integer greater than 0.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }

    return AmountInCents;
}