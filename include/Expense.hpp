#pragma once

#include <string>
#include <iomanip>

class Expense
{
private:
    std::string category;
    int amount_in_cents;
    std::string description;

public:
    Expense(std::string expense_category,
            int expense_amount_in_cents,
            std::string expense_description);

    friend std::ostream &operator<<(
        std::ostream &os,
        const Expense &expense);

    int getAmount() const;

    const std::string &getCategory() const;

    const std::string &getDescription() const;

    void setCategory(const std::string &new_category);

    void setAmountInCents(int new_amount_in_cents);

    void setDescription(const std::string &);

};