#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

#include "ExpenseTracker.hpp"

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
                tracker.SaveExpenses();
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
