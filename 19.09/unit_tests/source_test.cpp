#include "header.h"
#include "catch.hpp"

TEST_CASE("Test test", "[Dummy]") {
    SECTION("Default construction") {
        REQUIRE_NOTHROW(Dummy());
    }
    SECTION("Execute doSmth method") {
        REQUIRE_NOTHROW(Dummy().doSmth());
    }
}