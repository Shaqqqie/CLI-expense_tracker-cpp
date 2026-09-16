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
    tracker.loadExpenses();
    while (true)
    {
        std::cout << "\nExpense tracker\n";
        std::cout << "1. Add expense\n";
        std::cout << "2. View expenses\n";
        std::cout << "3. Show total\n";
        std::cout << "4. Delete expense\n";
        std::cout << "5. Edit expense\n";
        std::cout << "6. Sort expenses\n";
        std::cout << "7. Show summary\n";
        std::cout << "8. Exit\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> input))
        {
            std::cout << "\nNot valid input.\n";

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');
        }
        else if (input < 1 || input > 8)
        {
            std::cout << "\nChoose a valid option\n";
        }
        else
        {
            switch (input)
            {
            case 1:
                tracker.addExpense();
                std::cout << "Expense succesfully added.\n";
                tracker.saveExpenses();
                break;
            case 2:
            {
                tracker.viewExpenses();
                char input{};
                std::cout << "Filter by category?(y/n)\n";
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                if (std::cin >> input && (input == 'Y' || input == 'y'))
                {
                    tracker.viewExpensesByCategory();
                    break;
                }
                else
                {
                    break;
                }
            }
            case 3:
                tracker.showTotal();
                break;
            case 4:
                tracker.deleteExpense();
                tracker.saveExpenses();
                std::cout << "Expense succesfully deleted.\n";
                break;
            case 5:
                tracker.editExpense();
                tracker.saveExpenses();
                break;
            case 6:
                tracker.sortExpenses();
                break;
            case 7:
                tracker.showSummary();
                break;
            case 8:
                std::cout << "Exiting Expense Tracker...\n";
                break;
            }

            if (input == 8)
            {
                break;
            }
        }
    }

    return 0;
}
