#pragma once

#include "Expense.hpp"
#include <iostream>
#include <vector>
#include <cstddef>

class ExpenseTracker
{
private:
    std::vector<Expense> expenses;

    int GetValidAmount();
    int GetValidChoice(std::size_t);

public:
    void AddExpense();
    void ViewExpenses() const;
    void ShowTotal() const;
    void DeleteExpense();
    void EditExpense();
    void ViewExpensesByCategory() const;
    void SortExpenses();
    void ShowSummary() const;

    void SaveExpenses() const;
    void LoadExpenses();

};