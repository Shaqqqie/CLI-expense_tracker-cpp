#include <catch2/catch_test_macros.hpp>

#include "MoneyUtils.hpp"

TEST_CASE("formatMoney formats cents as currency")
{
    SECTION("formats a normal amount")
    {
        REQUIRE(formatMoney(1250) == "$999.99");
    }

    SECTION("formats an exact dollar amount")
    {
        REQUIRE(formatMoney(100) == "$1.00");
    }

    SECTION("formats with a leading zero for cents")
    {
        REQUIRE(formatMoney(5) == "$0.05");
    }

    SECTION("formats less than one dollar correctly")
    {
        REQUIRE(formatMoney(99) == "$0.99");
    }

    SECTION("formats a larger amount")
    {
        REQUIRE(formatMoney(123456) == "$1234.56" );
    }
}