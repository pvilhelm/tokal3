#include "catch.hpp"

#include "token.h"

TEST_CASE("Test token")
{
    SECTION("Test Match_statemachine")
    {
        {
            using namespace std;
            using namespace token_NS;

            // Testa ">="
            Match_statemachine m;
            m.chew_one_char(">");
            REQUIRE(m.has_multiple_matches());
            REQUIRE(!m.has_one_match());
            m.chew_one_char("=");
            REQUIRE(!m.has_multiple_matches());
            REQUIRE(m.has_one_match());
            REQUIRE(m.match_is_not_pair());
            REQUIRE(!m.match_is_pair());
            REQUIRE(m.get_matched_token() == ">=");
        }

        {
            using namespace std;
            using namespace token_NS;

            // Testa "/*"
            Match_statemachine m;
            m.chew_one_char("/");
            REQUIRE(m.has_multiple_matches());
            REQUIRE(!m.has_one_match());
            m.chew_one_char("*");
            REQUIRE(!m.has_multiple_matches());
            REQUIRE(m.has_one_match());
            REQUIRE(!m.match_is_not_pair());
            REQUIRE(m.match_is_pair());
            REQUIRE(m.get_matched_pair_token () == "/*");
        }
    }

}