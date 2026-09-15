#pragma once

#include <iostream>
#include <string>
#include <iomanip>

class Expense
{
private:
    std::string category;
    int AmountInCents;
    std::string description;

public:
    Expense(std::string ExpenseCategory,
            int ExpenseAmountInCents,
            std::string ExpenseDescription);

    friend std::ostream &operator<<(
        std::ostream &os,
        const Expense &expense);

    int GetAmount() const;

    const std::string &GetCategory() const;

    const std::string &GetDescription() const;

    void SetCategory(const std::string &);

    void SetAmountInCents(int);

    void SetDescription(const std::string &);

};