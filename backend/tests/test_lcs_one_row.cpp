#include "catch.hpp"
#include "../lcs/lcs_one_row.h"

TEST_CASE("LCS_OneRow - 公共子序列正常情况", "[LCS_OneRow]") {
    SECTION("经典用例 abcde / ace") {
        REQUIRE(LCS_OneRow::solve("abcde", "ace") == 3);
    }

    SECTION("部分匹配 oxcpqrsvwf / shmtulqrypy") {
        REQUIRE(LCS_OneRow::solve("oxcpqrsvwf", "shmtulqrypy") == 2);
    }

    SECTION("单个公共字符 bsbininm / jmjkbkjkv") {
        REQUIRE(LCS_OneRow::solve("bsbininm", "jmjkbkjkv") == 1);
    }

    SECTION("长字符串公共子序列") {
        REQUIRE(LCS_OneRow::solve("abcdefghij", "acegj") == 5);
    }

    SECTION("交错公共子序列 abac / cab") {
        REQUIRE(LCS_OneRow::solve("abac", "cab") == 2);
    }
}

TEST_CASE("LCS_OneRow - 两字符串完全相同", "[LCS_OneRow]") {
    SECTION("完全相同 abc / abc") {
        REQUIRE(LCS_OneRow::solve("abc", "abc") == 3);
    }

    SECTION("单字符相同 a / a") {
        REQUIRE(LCS_OneRow::solve("a", "a") == 1);
    }

    SECTION("长字符串完全相同") {
        string s = "abcdefghijklmnopqrstuvwxyz";
        REQUIRE(LCS_OneRow::solve(s, s) == 26);
    }
}

TEST_CASE("LCS_OneRow - 无公共子序列", "[LCS_OneRow]") {
    SECTION("完全不同 abc / def") {
        REQUIRE(LCS_OneRow::solve("abc", "def") == 0);
    }

    SECTION("单字符不同 a / b") {
        REQUIRE(LCS_OneRow::solve("a", "b") == 0);
    }

    SECTION("长度差异大但无公共字符") {
        REQUIRE(LCS_OneRow::solve("abcde", "xyz") == 0);
    }
}

TEST_CASE("LCS_OneRow - 空字符串情况", "[LCS_OneRow]") {
    SECTION("text1 为空") {
        REQUIRE(LCS_OneRow::solve("", "abc") == 0);
    }

    SECTION("text2 为空") {
        REQUIRE(LCS_OneRow::solve("abc", "") == 0);
    }

    SECTION("两者均为空") {
        REQUIRE(LCS_OneRow::solve("", "") == 0);
    }
}

TEST_CASE("LCS_OneRow - 交换参数结果一致", "[LCS_OneRow]") {
    SECTION("长短字符串交换") {
        REQUIRE(LCS_OneRow::solve("abcde", "ace") == LCS_OneRow::solve("ace", "abcde"));
    }

    SECTION("等长字符串交换") {
        REQUIRE(LCS_OneRow::solve("abc", "def") == LCS_OneRow::solve("def", "abc"));
    }
}
