#include "MoneyUtils.hpp"
#include <iomanip>
#include <sstream>

std::string formatMoney(int amount_in_cents)
{
    std::ostringstream amount{};

    amount << '$';
    amount << amount_in_cents / 100;
    amount << '.';
    amount << std::setfill('0');
    amount << std::setw(2);
    amount << amount_in_cents % 100;

    return amount.str();
}