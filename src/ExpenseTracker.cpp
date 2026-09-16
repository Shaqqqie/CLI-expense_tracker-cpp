#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>

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
    std::cout << "Choose expense to delete(number): ";
    int ExpenseToDelete{GetValidChoice(expenses.size())};

    expenses.erase(expenses.begin() + (ExpenseToDelete - 1));
}

void ExpenseTracker::EditExpense()
{
    if (expenses.empty())
    {
        std::cout << "There are no expenses to edit.\n";
        return;
    }

    ViewExpenses();
    std::cout << "Choose expense to edit: ";
    int ExpenseToEdit{GetValidChoice(expenses.size())};

    Expense &expense = expenses.at(ExpenseToEdit - 1);
    std::cout << "What would you like to edit?\n";
    std::cout << "1. Category\n";
    std::cout << "2. Amount\n";
    std::cout << "3. Description\n";
    std::cout << "4. Cancel\n";
    std::cout << "Choice: ";
    int edit{GetValidChoice(4)};

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

    while (true)
    {
        std::cout << "Enter amount in cents: ";

        if (std::cin >> AmountInCents && AmountInCents > 0)
        {
            break;
        }

        std::cout << "Amount must be an integer greater than 0.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');
    }

    return AmountInCents;
}

void ExpenseTracker::ViewExpensesByCategory() const
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
        if (expense.GetCategory() == category)
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

int ExpenseTracker::GetValidChoice(std::size_t max)
{
    int choice{};
    while (true)
    {
        if (std::cin >> choice && choice > 0 && choice <= static_cast<int>(max))
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

void ExpenseTracker::SortExpenses()
{
    std::cout << "\nSort expenses by:\n";
    std::cout << "1. Amount: Low to High\n";
    std::cout << "2. Amount: High to Low\n";
    std::cout << "3. Category: A-Z\n";
    std::cout << "4. Category: Z-A\n";
    std::cout << "5. Cancel\n";
    std::cout << "Choice: ";
    int choice{GetValidChoice(5)};

    if (choice == 1)
    {
        std::sort(expenses.begin(), expenses.end(),
                  [](const Expense &expense_a, const Expense &expense_b)
                  {
                      return expense_a.GetAmount() < expense_b.GetAmount();
                  });
    }
    else if (choice == 2)
    {
        std::sort(expenses.begin(), expenses.end(),
                  [](const Expense &expense_a, const Expense &expense_b)
                  {
                      return expense_a.GetAmount() > expense_b.GetAmount();
                  });
    }
    else if (choice == 3)
    {
        std::sort(expenses.begin(), expenses.end(),
                  [](const Expense &expense_a, const Expense &expense_b)
                  {
                      return expense_a.GetCategory() < expense_b.GetCategory();
                  });
    }
    else if (choice == 4)
    {
        std::sort(expenses.begin(), expenses.end(),
                  [](const Expense &expense_a, const Expense &expense_b)
                  {
                      return expense_a.GetCategory() > expense_b.GetCategory();
                  });
    }
    else
    {
        return;
    }
    ViewExpenses();
}

void ExpenseTracker::ShowSummary() const
{

    if (expenses.empty())
    {
        std::cout << "No expenses exist.\n";
        return;
    }

     int total{};
    for (const auto &expense : expenses)
    {
        total += expense.GetAmount();
    }

     int average{total / static_cast<int>(expenses.size())};

    std::cout << "\nExpense Summary\n";
    std::cout << std::setfill('-') << std::setw(20) << "\n";
    std::cout << "Number of expenses: " << expenses.size() << "\n";
    std::cout << "Total: $" << total / 100 << "." << std::setfill('0') << std::setw(2) << total % 100 << "\n";
    std::cout << "Average: $" << average / 100 << "." << std::setfill('0') << std::setw(2) << average % 100 << "\n";
}