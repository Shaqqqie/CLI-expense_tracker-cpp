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

public:
    void addExpense();
    void viewExpenses() const;
    void showTotal() const;
    void deleteExpense();
    void editExpense();
    void viewExpensesByCategory() const;
    void sortExpenses();
    void showSummary() const;

    void saveExpenses() const;
    void loadExpenses();

};