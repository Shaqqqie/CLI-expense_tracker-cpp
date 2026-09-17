#pragma once

#include "Expense.hpp"

#include <vector>
#include <cstddef>

class ExpenseTracker
{
private:
    std::vector<Expense> expenses;

    int getValidAmount() const;
    int getValidChoice(std::size_t max_choices) const;
    std::string getValidCategory() const;
    int calculateTotal() const;

public:
    void addExpense();
    void viewExpenses() const;
    void showTotal() const;
    bool deleteExpense();
    bool editExpense();
    void viewExpensesByCategory() const;
    void sortExpenses();
    void showSummary() const;

    void saveExpenses() const;
    void loadExpenses();

};