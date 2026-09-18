#include "ExpenseTracker.hpp"
#include "InputUtils.hpp"

#include <iostream>
#include <limits>

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
            {
                std::string category{getValidCategory()};
                int amount_in_cents{getValidAmount()};
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n');
                std::string description{};
                std::cout << "Enter a description: ";
                std::getline(std::cin, description);
                Expense expense{category, amount_in_cents, description};
                tracker.addExpense(expense);
                std::cout << "Expense successfully added.\n";
                tracker.saveExpenses();
                break;
            }
            case 2:
            {
                tracker.viewExpenses();
                char input{};
                std::cout << "Filter by category?(y/n)\n";
                if (std::cin >> input && (input == 'Y' || input == 'y'))
                {
                    tracker.viewExpensesByCategory();
                }
                break;
            }
            case 3:
                tracker.showTotal();
                break;
            case 4:
            {
                if (tracker.deleteExpense())
                {
                    tracker.saveExpenses();
                    std::cout << "Expense successfully deleted.\n";
                }
                break;
            }
            case 5:
            {
                if (tracker.getExpensesCount() == 0)
                {
                    std::cout << "No expenses to edit.\n";
                    break;
                }

                tracker.viewExpenses();
                std::cout << "Choose expense to edit: ";

                int expense_to_edit{getValidChoice(tracker.getExpensesCount())};
                std::size_t expense_index{static_cast<std::size_t>(expense_to_edit - 1)};
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
                    const std::string new_category{getValidCategory()};
                    if (tracker.editExpenseCategory(expense_index, new_category))
                    {
                        tracker.saveExpenses();
                        std::cout << "Edit successful\n";
                    }
                    break;
                }
                case 2:
                {
                    int new_amount_in_cents{getValidAmount()};
                    if (tracker.editExpenseAmount(expense_index, new_amount_in_cents))
                    {
                        tracker.saveExpenses();
                        std::cout << "Edit successful\n";
                    }
                    break;
                }
                case 3:
                {
                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(),
                        '\n');
                    std::string new_description{};
                    std::cout << "Enter new description: ";
                    std::getline(std::cin, new_description);
                    if (tracker.editExpenseDescription(expense_index, new_description))
                    {
                        tracker.saveExpenses();
                        std::cout << "Edit successful\n";
                    }
                    break;
                }
                case 4:
                default:
                    break;
                }
                break;
            }
            case 6:
                tracker.sortExpenses();
                break;
            case 7:
                tracker.showSummary();
                break;
            case 8:
                std::cout << "Exiting Expense Tracker...\n";
                return 0;
            default:
                std::cerr << "Invalid menu option.\n";
                break;
            }
        }
    }
}
