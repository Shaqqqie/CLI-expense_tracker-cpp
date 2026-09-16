#pragma once

#include "Expense.hpp"
#include <iostream>
#include <vector>
#include <cstddef>

class ExpenseTracker
{
private:
    std::vector<Expense> expenses;

    int getValidAmount();
    int getValidChoice(std::size_t);

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
    void LoadExpenses();

};