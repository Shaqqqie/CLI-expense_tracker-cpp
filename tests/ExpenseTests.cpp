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

TEST_CASE("Constructor throws exception for empty category")
{
    REQUIRE_THROWS_AS(Expense("", 1250, "Lunch"), std::invalid_argument);
}

TEST_CASE("setCategory throws exception for empty category")
{
    Expense expense("Food", 1250, "Lunch");
    REQUIRE_THROWS_AS(expense.setCategory(""), std::invalid_argument);
}

TEST_CASE("Constructor throws rejection when amount equals 0")
{
    REQUIRE_THROWS_AS(Expense("Food", 0, "Lunch"), std::invalid_argument);
}

TEST_CASE("setAmountInCents throws exception when new amount equals 0")
{
    Expense expense("Food", 1250, "Lunch");

    REQUIRE_THROWS_AS(expense.setAmountInCents(0), std::invalid_argument);
}