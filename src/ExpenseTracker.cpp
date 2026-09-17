#include "ExpenseTracker.hpp"
#include "MoneyUtils.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

void ExpenseTracker::addExpense()
{
    std::string category{getValidCategory()};

    int amount_in_cents{getValidAmount()};

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
    std::string description{};
    std::cout << "Enter a description: ";
    std::getline(std::cin, description);

    Expense expense(category, amount_in_cents, description);
    addExpense(expense);
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
    int total{getTotal()};

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
        if (!std::getline(stream, category, '|') || category.empty())
        {
            std::cerr << "Warning: empty category in save file. Skipping expense.\n";
            continue;
        }

        std::string amount{};
        if (!std::getline(stream, amount, '|') || amount.empty())
        {
            std::cerr << "Warning: no amount value in save file. Skipping expense.\n";
            continue;
        }

        std::string description{};
        std::getline(stream, description);

        try
        {
            std::size_t pos{};
            int amount_in_cents{std::stoi(amount, &pos)};

            if (pos < amount.size() || amount_in_cents <= 0)
            {
                std::cerr << "Warning: invalid amount in save file. Skipping expense.\n";
                continue;
            }

            Expense expense(category, amount_in_cents, description);
            expenses.push_back(expense);
        }
        catch (const std::invalid_argument &error)
        {
            std::cout << error.what() << "\n";
            std::cerr << "Warning: invalid amount in save file. Skipping expense.\n";
        }
        catch (const std::out_of_range &error)
        {
            std::cout << error.what() << "\n";
            std::cerr << "Warning: amount out of range in save file. Skipping expense.\n";
        }
    }
}

bool ExpenseTracker::deleteExpense()
{
    if (expenses.empty())
    {
        std::cout << "There are no expenses to be deleted.\n";
        return false;
    }
    viewExpenses();
    std::cout << "Choose expense to delete(number): ";
    int expense_to_delete{getValidChoice(expenses.size())};

    expenses.erase(expenses.begin() + (expense_to_delete - 1));
    return true;
}

bool ExpenseTracker::editExpense()
{
    if (expenses.empty())
    {
        std::cout << "There are no expenses to edit.\n";
        return false;
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
        std::string new_category{getValidCategory()};
        expense.setCategory(new_category);
        return true;
    }
    case 2:
    {
        int amount_in_cents{getValidAmount()};
        expense.setAmountInCents(amount_in_cents);

        return true;
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

        return true;
    }
    case 4:
    default:
        return false;
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
        if (std::cin >> choice && choice > 0 && std::cmp_less_equal(choice, max_choices))
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
        std::ranges::sort(expenses,
                          [](const Expense &expense_a, const Expense &expense_b)
                          {
                              return expense_a.getAmount() < expense_b.getAmount();
                          });
    }
    else if (choice == 2)
    {
        std::ranges::sort(expenses,
                          [](const Expense &expense_a, const Expense &expense_b)
                          {
                              return expense_a.getAmount() > expense_b.getAmount();
                          });
    }
    else if (choice == 3)
    {
        std::ranges::sort(expenses,
                          [](const Expense &expense_a, const Expense &expense_b)
                          {
                              return expense_a.getCategory() < expense_b.getCategory();
                          });
    }
    else if (choice == 4)
    {
        std::ranges::sort(expenses,
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

    int total{getTotal()};

    int average{total / static_cast<int>(expenses.size())};

    std::cout << "\nExpense Summary\n";
    std::cout << "---------------------------\n";
    std::cout << "Number of expenses: " << expenses.size() << "\n";
    std::cout << "Total: " << formatMoney(total) << "\n";
    std::cout << "Average: " << formatMoney(average) << "\n";
}

int ExpenseTracker::getTotal() const
{
    int total{};

    for (const auto &expense : expenses)
    {
        total += expense.getAmount();
    }

    return total;
}

std::string ExpenseTracker::getValidCategory() const
{
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
    std::string category{};
    while (true)
    {
        std::cout << "Enter category: ";
        std::getline(std::cin, category);

        if (!category.empty())
        {
            break;
        }

        std::cerr << "Category cannot be empty.\n";
    }

    return category;
}

void ExpenseTracker::addExpense(const Expense &expense)
{
    expenses.push_back(expense);
}