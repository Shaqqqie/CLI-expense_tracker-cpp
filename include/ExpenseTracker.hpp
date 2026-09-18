#pragma once

#include "Expense.hpp"

#include <cstddef>
#include <string>
#include <vector>

enum class SortOption
{
    AmountLowToHigh,
    AmountHighToLow,
    CategoryAZ,
    CategoryZA
};

class ExpenseTracker
{
private:
    std::vector<Expense> expenses;

public:
    // Modification
    void addExpense(const Expense &expense);
    bool deleteExpense(std::size_t index);
    bool editExpenseCategory(std::size_t index, const std::string &new_category);
    bool editExpenseAmount(std::size_t index, int amount_in_cents);
    bool editExpenseDescription(std::size_t index, const std::string &new_description);
    void sortExpenses(SortOption option);

    // Queries
    const std::vector<Expense> &getExpenses() const;
    std::vector<Expense> getExpensesByCategory(const std::string &category) const;
    int getTotal() const;
    std::size_t getExpensesCount() const;

    // Persistence
    void saveExpenses() const;
    void loadExpenses();
};