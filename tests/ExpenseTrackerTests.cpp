#include <catch2/catch_test_macros.hpp>

#include "Expense.hpp"
#include "ExpenseTracker.hpp"

// ----------------------------------------
// Add / Get Expenses
// ----------------------------------------

TEST_CASE("ExpenseTracker can add expenses")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});

    REQUIRE(tracker.getExpensesCount() == 1);
    REQUIRE(tracker.getExpenses().at(0).getCategory() == "Food");
    REQUIRE(tracker.getExpenses().at(0).getAmount() == 1250);
    REQUIRE(tracker.getExpenses().at(0).getDescription() == "Dinner");
}

// ----------------------------------------
// Total
// ----------------------------------------

TEST_CASE("ExpenseTracker calculates total")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});
    tracker.addExpense(Expense{"Transport", 450, "Bus Ticket"});
    tracker.addExpense(Expense{"Gaming", 3000, "New Game"});

    REQUIRE(tracker.getTotal() == 4700);
}

TEST_CASE("Empty ExpenseTracker has a total of zero")
{
    ExpenseTracker tracker;

    REQUIRE(tracker.getTotal() == 0);
}

// ------------------------------------------
// Delete
// ------------------------------------------

TEST_CASE("ExpenseTracker can delete an expense")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});
    tracker.addExpense(Expense{"Transport", 450, "Bus Ticket"});

    REQUIRE(tracker.deleteExpense(0));
    REQUIRE(tracker.getExpensesCount() == 1);

    REQUIRE(tracker.getExpenses().at(0).getCategory() == "Transport");
}

TEST_CASE("ExpenseTracker rejects invalid delete index")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});

    REQUIRE_FALSE(tracker.deleteExpense(4));
    REQUIRE(tracker.getExpensesCount() == 1);
}

// ------------------------------------------
// Edit
// ------------------------------------------

TEST_CASE("ExpenseTracker can edit expense category")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});

    REQUIRE(tracker.editExpenseCategory(0, "Groceries"));

    REQUIRE(tracker.getExpenses().at(0).getCategory() == "Groceries");
}

TEST_CASE("ExpenseTracker rejects empty category")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});

    REQUIRE_FALSE(tracker.editExpenseCategory(0, ""));

    REQUIRE(tracker.getExpenses().at(0).getCategory() == "Food");
}

TEST_CASE("ExpenseTracker can edit expense amount")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});

    REQUIRE(tracker.editExpenseAmount(0, 2000));
    REQUIRE(tracker.getExpenses().at(0).getAmount() == 2000);
}

TEST_CASE("ExpenseTracker rejects invalid expense amount")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});

    REQUIRE_FALSE(tracker.editExpenseAmount(0, -500));
    REQUIRE(tracker.getExpenses().at(0).getAmount() == 1250);
}

TEST_CASE("ExpenseTracker can edit expense description")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});

    REQUIRE(tracker.editExpenseDescription(0, "Dinner with friends"));

    REQUIRE(
        tracker.getExpenses().at(0).getDescription() == "Dinner with friends");
}

TEST_CASE("ExpenseTracker rejects invalid edit index")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});

    REQUIRE_FALSE(tracker.editExpenseCategory(4, "Transport"));

    REQUIRE_FALSE(tracker.editExpenseAmount(4, 5000));

    REQUIRE_FALSE(tracker.editExpenseDescription(4, "Test"));
}

// ------------------------------------------
// Filtering
// ------------------------------------------

TEST_CASE("ExpenseTracker filters expenses by category")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});
    tracker.addExpense(Expense{"Transport", 450, "Bus Ticket"});
    tracker.addExpense(Expense{"Food", 800, "Breakfast"});

    const std::vector<Expense> filtered{
        tracker.getExpensesByCategory("Food")};

    REQUIRE(filtered.size() == 2);
    REQUIRE(filtered.at(0).getCategory() == "Food");
    REQUIRE(filtered.at(1).getCategory() == "Food");
}

TEST_CASE("Filtering unknown category returns empty vector")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});

    const std::vector<Expense> filtered{
        tracker.getExpensesByCategory("Gaming")};

    REQUIRE(filtered.empty());
}

// ------------------------------------------
// Sorting
// ------------------------------------------

TEST_CASE("ExpenseTracker sorts amount low to high")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});
    tracker.addExpense(Expense{"Gaming", 3000, "New Game"});
    tracker.addExpense(Expense{"Transport", 450, "Bus Ticket"});

    tracker.sortExpenses(SortOption::AmountLowToHigh);

    const auto &expenses{tracker.getExpenses()};

    REQUIRE(expenses.at(0).getAmount() == 450);
    REQUIRE(expenses.at(1).getAmount() == 1250);
    REQUIRE(expenses.at(2).getAmount() == 3000);
}

TEST_CASE("ExpenseTracker sorts amount high to low")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});
    tracker.addExpense(Expense{"Gaming", 3000, "New Game"});
    tracker.addExpense(Expense{"Transport", 450, "Bus Ticket"});

    tracker.sortExpenses(SortOption::AmountHighToLow);

    const auto &expenses{tracker.getExpenses()};

    REQUIRE(expenses.at(0).getAmount() == 3000);
    REQUIRE(expenses.at(1).getAmount() == 1250);
    REQUIRE(expenses.at(2).getAmount() == 450);
}

TEST_CASE("ExpenseTracker sorts categories A to Z")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Transport", 450, "Bus"});
    tracker.addExpense(Expense{"Gaming", 3000, "Game"});
    tracker.addExpense(Expense{"Food", 1250, "Lunch"});

    tracker.sortExpenses(SortOption::CategoryAZ);

    const auto &expenses{tracker.getExpenses()};

    REQUIRE(expenses.at(0).getCategory() == "Food");
    REQUIRE(expenses.at(1).getCategory() == "Gaming");
    REQUIRE(expenses.at(2).getCategory() == "Transport");
}

TEST_CASE("ExpenseTracker sorts categories Z to A")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Lunch"});
    tracker.addExpense(Expense{"Transport", 450, "Bus"});
    tracker.addExpense(Expense{"Gaming", 3000, "Game"});

    tracker.sortExpenses(SortOption::CategoryZA);

    const auto &expenses{tracker.getExpenses()};

    REQUIRE(expenses.at(0).getCategory() == "Transport");
    REQUIRE(expenses.at(1).getCategory() == "Gaming");
    REQUIRE(expenses.at(2).getCategory() == "Food");
}