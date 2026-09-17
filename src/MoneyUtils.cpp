#include "MoneyUtils.hpp"
#include <iomanip>
#include <sstream>

namespace
{
    constexpr int cents_per_dollar{100};
}

std::string formatMoney(int amount_in_cents)
{
    std::ostringstream amount{};

    amount << '$';
    amount << amount_in_cents / cents_per_dollar;
    amount << '.';
    amount << std::setfill('0');
    amount << std::setw(2);
    amount << amount_in_cents % cents_per_dollar;

    return amount.str();
}