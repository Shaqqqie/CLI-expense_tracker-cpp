#pragma once

#include "Expense.hpp"
#include <iostream>
#include <vector>

class ExpenseTracker
{
private:
    std::vector<Expense> expenses;

public:
    void AddExpense();
    void ViewExpenses() const;
    void ShowTotal() const;

    void SaveExpenses() const;
};