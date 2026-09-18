#include "ExpenseTracker.hpp"
#include "MoneyUtils.hpp"
#include "InputUtils.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

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

bool ExpenseTracker::deleteExpense(std::size_t index)
{
    if (index >= expenses.size())
    {
        return false;
    }
    
    const auto offset{
        static_cast<std::vector<Expense>::difference_type>(index)
    };

    expenses.erase(expenses.begin() + offset);
    return true;
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

void ExpenseTracker::addExpense(const Expense &expense)
{
    expenses.push_back(expense);
}

std::size_t ExpenseTracker::getExpensesCount() const
{
    return expenses.size();
}

bool ExpenseTracker::editExpenseCategory(std::size_t index, const std::string &new_category)
{
    if (index >= expenses.size() || new_category.empty())
    {
        return false;
    }
    
    Expense &expense = expenses.at(index);
    expense.setCategory(new_category); 
    
    return true;
}

bool ExpenseTracker::editExpenseAmount(std::size_t index, int amount_in_cents)
{
    if (index >= expenses.size() || amount_in_cents <= 0)
    {
        return false;
    }

    Expense &expense = expenses.at(index);
    expense.setAmountInCents(amount_in_cents);

    return true;

}

bool ExpenseTracker::editExpenseDescription(std::size_t index, const std::string &new_description)
{
    if (index >= expenses.size())
    {
        return false;
    }

    Expense &expense = expenses.at(index);
    expense.setDescription(new_description);

    return true;
}