#include "InputUtils.hpp"

#include <iostream>
#include <limits>
#include <utility>

int getValidAmount()
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

int getValidChoice(std::size_t max_choices)
{
    int choice{};
    while(true)
    {
        if(std::cin >> choice && choice > 0 && std::cmp_less_equal(choice, max_choices))
        {
            return choice;
        }

        std::cout << "Choose a valid option: ";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

std::string getValidCategory()
{
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );
    std::string category{};
    while(true)
    {
        std::cout << "Enter category: ";
        std::getline(std::cin, category);

        if(!category.empty())
        {
            break;
        }

        std::cerr << "Category cannot be empty.\n";
    }

    return category;
}