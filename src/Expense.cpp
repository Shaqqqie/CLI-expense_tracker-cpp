#include <iostream>
#include <string>
#include <iomanip>

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
    const Expense &expense
)
{
    os << "\nCategory: " << expense.category << "\n";
    os << "Amount: $" << expense.AmountInCents / 100 << "." << std::setfill('0') << std::setw(2) << expense.AmountInCents % 10 << "\n";
    os << "Description: " << expense.description << "\n";
}
