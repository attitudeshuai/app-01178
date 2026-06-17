#include "catch.hpp"
#include "../lcs/lcs_validator.h"

TEST_CASE("isValidInput - 合法输入", "[validator]") {
    SECTION("全小写字母") {
        REQUIRE(isValidInput("abc") == true);
    }

    SECTION("单字符") {
        REQUIRE(isValidInput("a") == true);
        REQUIRE(isValidInput("z") == true);
    }

    SECTION("空字符串") {
        REQUIRE(isValidInput("") == true);
    }

    SECTION("全部26个小写字母") {
        REQUIRE(isValidInput("abcdefghijklmnopqrstuvwxyz") == true);
    }
}

TEST_CASE("isValidInput - 非法字符容错处理", "[validator]") {
    SECTION("包含大写字母") {
        REQUIRE(isValidInput("Abc") == false);
        REQUIRE(isValidInput("ABC") == false);
        REQUIRE(isValidInput("abC") == false);
    }

    SECTION("包含数字") {
        REQUIRE(isValidInput("abc123") == false);
        REQUIRE(isValidInput("123") == false);
        REQUIRE(isValidInput("a1b") == false);
    }

    SECTION("包含特殊字符") {
        REQUIRE(isValidInput("abc!") == false);
        REQUIRE(isValidInput("a b") == false);
        REQUIRE(isValidInput("a@b") == false);
        REQUIRE(isValidInput("a#b") == false);
        REQUIRE(isValidInput("a$b") == false);
    }

    SECTION("包含空格") {
        REQUIRE(isValidInput("ab c") == false);
        REQUIRE(isValidInput(" ") == false);
    }

    SECTION("包含中文") {
        REQUIRE(isValidInput("abc中文") == false);
    }

    SECTION("边界字符 - 'a'的前一个字符") {
        string s;
        s += ('a' - 1);
        REQUIRE(isValidInput(s) == false);
    }

    SECTION("边界字符 - 'z'的后一个字符") {
        string s;
        s += ('z' + 1);
        REQUIRE(isValidInput(s) == false);
    }
}
