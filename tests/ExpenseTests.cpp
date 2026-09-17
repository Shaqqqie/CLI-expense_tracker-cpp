#include <catch2/catch_test_macros.hpp>

#include "Expense.hpp"

TEST_CASE("Expense stores its initial values")
{
    Expense expense("Food", 1250, "Dinner");

    REQUIRE(expense.getCategory() == "Food");
    REQUIRE(expense.getAmount() == 1250);
    REQUIRE(expense.getDescription() == "Dinner");
}

TEST_CASE("Expense setters update its values")
{
    Expense expense("Food", 1250, "Dinner");

    expense.setCategory("Transport");
    expense.setAmountInCents(500);
    expense.setDescription("Bus Ticket");

    REQUIRE(expense.getCategory() == "Transport");
    REQUIRE(expense.getAmount() == 500);
    REQUIRE(expense.getDescription() == "Bus Ticket");
}

