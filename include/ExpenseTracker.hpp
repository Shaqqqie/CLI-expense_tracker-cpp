#pragma once

#include "Expense.hpp"

#include <vector>
#include <cstddef>

enum class SortOption
{
    AmountLowtoHigh,
    AmountHightoLow,
    CategoryAZ,
    CategoryZA
};

class ExpenseTracker
{
private:
    std::vector<Expense> expenses;

public:
        void addExpense(const Expense &expense);
    void viewExpenses() const;
    void showTotal() const;
    bool deleteExpense(std::size_t index);
    void viewExpensesByCategory() const;
    void sortExpenses(SortOption option);
    void showSummary() const;
    int getTotal() const;
    std::size_t getExpensesCount() const;
    bool editExpenseCategory(std::size_t index, const std::string &new_category);
    bool editExpenseAmount(std::size_t index, int amount_in_cents);
    bool editExpenseDescription(std::size_t index, const std::string &new_description);

    void saveExpenses() const;
    void loadExpenses();
};