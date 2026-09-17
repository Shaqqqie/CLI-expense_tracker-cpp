#include <iomanip>
#include <utility>

#include "Expense.hpp"
#include "MoneyUtils.hpp"

Expense::Expense(std::string expense_category,
                 int expense_amount_in_cents,
                 std::string expense_description)
    : category{std::move(expense_category)},
      amount_in_cents{expense_amount_in_cents},
      description{std::move(expense_description)}
{
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
    category = new_category;
}

void Expense::setAmountInCents(int new_amount_in_cents)
{
    amount_in_cents = new_amount_in_cents;
}

void Expense::setDescription(const std::string &new_description)
{
    description = new_description;
}
