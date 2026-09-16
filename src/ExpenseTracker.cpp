#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "ExpenseTracker.hpp"
#include "Expense.hpp"
#include "MoneyUtils.hpp"

void ExpenseTracker::addExpense()
{
    std::string category{};
    std::cout << "\nEnter Category: ";
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
    std::getline(std::cin, category);

    int amount_in_cents{getValidAmount()};

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
    std::string description{};
    std::cout << "Enter a description: ";
    std::getline(std::cin, description);

    Expense expense(category, amount_in_cents, description);
    expenses.push_back(expense);
}

void ExpenseTracker::viewExpenses() const
{
    std::cout << "\n";
    for (std::size_t i{0}; i < expenses.size(); ++i)
    {
        std::cout << i + 1 << ". " << expenses.at(i) << "\n";
    }
    std::cout << "\n";
}

void ExpenseTracker::showTotal() const
{
    int total{};
    for (const auto &expense : expenses)
    {
        total += expense.getAmount();
    }

    std::cout << formatMoney(total) << "\n";
}

void ExpenseTracker::saveExpenses() const
{
    std::ofstream file{"data/expenses.txt"};

    if (!file)
    {
        std::cout << "Could not open file\n";
        return;
    }

    for (const auto &expense : expenses)
    {
        file << expense.getCategory()
             << "|" << expense.getAmount() << "|"
             << expense.getDescription() << "\n";
    }
}

void ExpenseTracker::loadExpenses()
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

        int amount_in_cents{std::stoi(amount)};

        Expense expense(category, amount_in_cents, description);
        expenses.push_back(expense);
    }
}

void ExpenseTracker::deleteExpense()
{
    if (expenses.empty())
    {
        std::cout << "There are no expenses to be deleted.\n";
        return;
    }
    viewExpenses();
    std::cout << "Choose expense to delete(number): ";
    int expense_to_delete{getValidChoice(expenses.size())};

    expenses.erase(expenses.begin() + (expense_to_delete - 1));
}

void ExpenseTracker::editExpense()
{
    if (expenses.empty())
    {
        std::cout << "There are no expenses to edit.\n";
        return;
    }

    viewExpenses();
    std::cout << "Choose expense to edit: ";
    int expense_to_edit{getValidChoice(expenses.size())};

    Expense &expense = expenses.at(expense_to_edit - 1);
    std::cout << "What would you like to edit?\n";
    std::cout << "1. Category\n";
    std::cout << "2. Amount\n";
    std::cout << "3. Description\n";
    std::cout << "4. Cancel\n";
    std::cout << "Choice: ";
    int edit{getValidChoice(4)};

    switch (edit)
    {
    case 1:
    {
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
        std::string new_category{};
        std::cout << "Enter New Category: ";
        std::getline(std::cin, new_category);
        expense.setCategory(new_category);
        std::cout << "Edit successful.\n";
        break;
    }
    case 2:
    {
        int amount_in_cents{getValidAmount()};
        expense.setAmountInCents(amount_in_cents);
        std::cout << "Edit successful.\n";
        break;
    }
    case 3:
    {
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
        std::string new_description{};
        std::cout << "Enter New Description: ";
        std::getline(std::cin, new_description);
        expense.setDescription(new_description);
        std::cout << "Edit successful.\n";
        break;
    }
    case 4:
        break;
    }
}

int ExpenseTracker::getValidAmount() const
{
    int amount_in_cents{};

    while (true)
    {
        std::cout << "Enter amount in cents: ";

        if (std::cin >> amount_in_cents && amount_in_cents > 0)
        {
            break;
        }

        std::cout << "Amount must be an integer greater than 0.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
    }

    return amount_in_cents;
}

void ExpenseTracker::viewExpensesByCategory() const
{

    if (expenses.empty())
    {
        std::cout << "No expenses to filter by category.\n";
        std::cout << "Make sure to add expenses first.\n";
        return;
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');

    std::string category{};
    std::cout << "Enter category: ";
    std::getline(std::cin, category);
    int index{1};

    for (const auto &expense : expenses)
    {
        if (expense.getCategory() == category)
        {
            std::cout << index << "." << expense << "\n";
            ++index;
        }
    }

    if (index == 1)
    {
        std::cout << "No matching expenses with that category.\n";
    }
}

int ExpenseTracker::getValidChoice(std::size_t max_choices) const
{
    int choice{};
    while (true)
    {
        if (std::cin >> choice && choice > 0 && static_cast<std::size_t>(choice) <= max_choices)
        {
            return choice;
        }

        std::cout << "Choose a valid option: ";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
    }
}

void ExpenseTracker::sortExpenses()
{
    std::cout << "\nSort expenses by:\n";
    std::cout << "1. Amount: Low to High\n";
    std::cout << "2. Amount: High to Low\n";
    std::cout << "3. Category: A-Z\n";
    std::cout << "4. Category: Z-A\n";
    std::cout << "5. Cancel\n";
    std::cout << "Choice: ";
    int choice{getValidChoice(5)};

    if (choice == 1)
    {
        std::sort(expenses.begin(), expenses.end(),
                  [](const Expense &expense_a, const Expense &expense_b)
                  {
                      return expense_a.getAmount() < expense_b.getAmount();
                  });
    }
    else if (choice == 2)
    {
        std::sort(expenses.begin(), expenses.end(),
                  [](const Expense &expense_a, const Expense &expense_b)
                  {
                      return expense_a.getAmount() > expense_b.getAmount();
                  });
    }
    else if (choice == 3)
    {
        std::sort(expenses.begin(), expenses.end(),
                  [](const Expense &expense_a, const Expense &expense_b)
                  {
                      return expense_a.getCategory() < expense_b.getCategory();
                  });
    }
    else if (choice == 4)
    {
        std::sort(expenses.begin(), expenses.end(),
                  [](const Expense &expense_a, const Expense &expense_b)
                  {
                      return expense_a.getCategory() > expense_b.getCategory();
                  });
    }
    else
    {
        return;
    }
    viewExpenses();
}

void ExpenseTracker::showSummary() const
{

    if (expenses.empty())
    {
        std::cout << "No expenses exist.\n";
        return;
    }

    int total{};
    for (const auto &expense : expenses)
    {
        total += expense.getAmount();
    }

    int average{total / static_cast<int>(expenses.size())};

    std::cout << "\nExpense Summary\n";
    std::cout << std::setfill('-') << std::setw(20) << "\n";
    std::cout << "Number of expenses: " << expenses.size() << "\n";
    std::cout << "Total: " << formatMoney(total) << "\n";
    std::cout << "Average: " << formatMoney(average) << "\n";
}
