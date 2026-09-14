#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

class Expense
{
private:
    std::string category;
    int AmountInCents;
    std::string description;

public:
    Expense(std::string ExpenseCategory, int ExpenseAmountInCents, std::string ExpenseDescription)
        : category{ExpenseCategory},
          AmountInCents{ExpenseAmountInCents},
          description{ExpenseDescription}
    {
    }

    friend std::ostream &operator<<(
        std::ostream &os,
        const Expense &expense)
    {
        os << "\nCategory: " << expense.category << "\n";
        os << "Amount: $" << expense.AmountInCents / 100 << "." << std::setfill('0') << std::setw(2) << expense.AmountInCents % 100 << "\n";
        os << "Description: " << expense.description << "\n";

        return os;
    }

    int GetAmount() const
    {
        return AmountInCents;
    }

    std::string GetCategory() const
    {
        return category;
    }

    std::string GetDescription() const
    {
        return description;
    }
};

class ExpenseTracker
{
private:
    std::vector<Expense> expenses;

public:
    void AddExpense();
    void ViewExpenses() const;
    void ShowTotal() const;
};

int main()
{
    int input{};
    ExpenseTracker tracker;
    while (true)
    {
        std::cout << "\nExpense tracker\n";
        std::cout << "1. Add expense\n";
        std::cout << "2. View expenses\n";
        std::cout << "3. Show total\n";
        std::cout << "4. Save expenses\n";
        std::cout << "5. Load expenses\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> input))
        {
            std::cout << "\nNot valid input.\n";

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');
        }
        else if (input < 1 || input > 6)
        {
            std::cout << "\nChoose a valid option\n";
        }
        else
        {
            switch (input)
            {
            case 1:
                tracker.AddExpense();
                std::cout << "Expense succesfully added.\n";
                break;
            case 2:
                tracker.ViewExpenses();
                break;
            case 3:
                tracker.ShowTotal();
                break;
            case 4:
                tracker.SaveExpenses();
                break;
            case 5:

                break;
            case 6:
                std::cout << "Exiting Expense Tracker...\n";
                break;
            }

            if (input == 6)
            {
                break;
            }
        }
    }

    return 0;
}

void ExpenseTracker::AddExpense()
{
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

        if (std::cin >> AmountInCents && AmountInCents > 0)
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
    std::getline(std::cin, description);

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
