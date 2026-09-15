#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

#include "Expense.hpp"

Expense::Expense(std::string ExpenseCategory,
                 int ExpenseAmountInCents,
                 std::string ExpenseDescription)
    : category{ExpenseCategory},
      AmountInCents{ExpenseAmountInCents},
      description{ExpenseDescription}
{
}

int Expense::GetAmount() const
{
    return AmountInCents;
}

const std::string &Expense::GetCategory() const
{
    return category;
}

const std::string &Expense::GetDescription() const
{
    return description;
}

std::ostream &operator<<(
    std::ostream &os,
    const Expense &expense)
{
    std::ostringstream amount;

    amount << '$';
    amount << expense.AmountInCents / 100;
    amount << '.';
    amount << std::setfill('0');
    amount << std::setw(2);
    amount << expense.AmountInCents % 100;

    os << std::left << std::setfill(' ') << std::setw(15) << expense.category;
    os << std::right << std::setw(10) << amount.str();
    os << std::setfill(' ') << std::right << std::setw(20) << expense.description;

    return os;
}

void Expense::SetCategory(const std::string &NewCategory)
{
    category = NewCategory;
}

void Expense::SetAmountInCents(int NewAmountInCents)
{
    AmountInCents = NewAmountInCents;
}

void Expense::SetDescription(const std::string &NewDescription)
{
    description = NewDescription;
}

