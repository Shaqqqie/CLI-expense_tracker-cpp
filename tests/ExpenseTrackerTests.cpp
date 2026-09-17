#include <catch2/catch_test_macros.hpp>

#include "ExpenseTracker.hpp"

TEST_CASE("Verify correct total calculation")
{
    ExpenseTracker tracker;

    tracker.addExpense(Expense{"Food", 1250, "Dinner"});
    tracker.addExpense(Expense{"Transport", 450, "Bus Ticket"});
    tracker.addExpense(Expense{"Gaming", 3000, "Game"});

    REQUIRE(tracker.getTotal() == 4700);
}

TEST_CASE("no expenses for getTotal")
{
    ExpenseTracker tracker;

    REQUIRE(tracker.getTotal() == 0);
}