#pragma once

#include "Expense.hpp"
#include <iostream>
#include <vector>

class ExpenseTracker
{
private:
    std::vector<Expense> expenses;

    int GetValidAmount();

public:
    void AddExpense();
    void ViewExpenses() const;
    void ShowTotal() const;
    void DeleteExpense();
    void EditExpense();
    void ViewExpensesByCategory() const;

    void SaveExpenses() const;
    void LoadExpenses();

};