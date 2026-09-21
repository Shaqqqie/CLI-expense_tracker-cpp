#include "Expense.hpp"
#include "MoneyUtils.hpp"

#include <iomanip>
#include <stdexcept>
#include <utility>

Expense::Expense(std::string expense_category,
                 int expense_amount_in_cents,
                 std::string expense_description)
    : category{std::move(expense_category)},
      amount_in_cents{expense_amount_in_cents},
      description{std::move(expense_description)}
{
    if (category.empty())
    {
        throw std::invalid_argument{"Category cannot be empty."};
    }

    if (amount_in_cents <= 0)
    {
        throw std::invalid_argument{"Amount must be greater than 0."};
    }
}

int Expense::getAmount() const
{
    return amount_in_cents;
}

const std::string &Expense::getCategory() const
{
    return category;
}

const std::string &Expense::getDescription() const
{
    return description;
}

std::ostream &operator<<(
    std::ostream &os,
    const Expense &expense)
{
    os << " " << std::left << std::setfill(' ') << std::setw(15) << expense.category;
    os << std::right << std::setw(10) << formatMoney(expense.amount_in_cents);
    os << std::right << std::setw(20) << expense.description;

    return os;
}

void Expense::setCategory(const std::string &new_category)
{
    if (new_category.empty())
    {
        throw std::invalid_argument{"Category cannot be empty"};
    }
    category = new_category;
}

void Expense::setAmountInCents(int new_amount_in_cents)
{
    if (new_amount_in_cents <= 0)
    {
        throw std::invalid_argument{"Amount must be greater than 0"};
    }
    amount_in_cents = new_amount_in_cents;
}

void Expense::setDescription(const std::string &new_description)
{
    description = new_description;
}
