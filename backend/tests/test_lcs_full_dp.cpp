#include "catch.hpp"
#include "../lcs/lcs_full_dp.h"

TEST_CASE("LCS_FullDP - 公共子序列正常情况", "[LCS_FullDP]") {
    string lcs;

    SECTION("经典用例 abcde / ace") {
        int len = LCS_FullDP::solve("abcde", "ace", lcs);
        REQUIRE(len == 3);
        REQUIRE(lcs == "ace");
    }

    SECTION("部分匹配 oxcpqrsvwf / shmtulqrypy") {
        int len = LCS_FullDP::solve("oxcpqrsvwf", "shmtulqrypy", lcs);
        REQUIRE(len == 2);
        REQUIRE(lcs == "qr");
    }

    SECTION("单个公共字符 bsbininm / jmjkbkjkv") {
        int len = LCS_FullDP::solve("bsbininm", "jmjkbkjkv", lcs);
        REQUIRE(len == 1);
        REQUIRE(lcs.length() == 1);
        REQUIRE((lcs == "b" || lcs == "m"));
    }

    SECTION("长字符串公共子序列") {
        int len = LCS_FullDP::solve("abcdefghij", "acegj", lcs);
        REQUIRE(len == 5);
        REQUIRE(lcs == "acegj");
    }

    SECTION("交错公共子序列") {
        int len = LCS_FullDP::solve("abac", "cab", lcs);
        REQUIRE(len == 2);
        REQUIRE((lcs == "ab" || lcs == "ac"));
    }
}

TEST_CASE("LCS_FullDP - 两字符串完全相同", "[LCS_FullDP]") {
    string lcs;

    SECTION("完全相同 abc / abc") {
        int len = LCS_FullDP::solve("abc", "abc", lcs);
        REQUIRE(len == 3);
        REQUIRE(lcs == "abc");
    }

    SECTION("单字符相同 a / a") {
        int len = LCS_FullDP::solve("a", "a", lcs);
        REQUIRE(len == 1);
        REQUIRE(lcs == "a");
    }

    SECTION("长字符串完全相同") {
        string s = "abcdefghijklmnopqrstuvwxyz";
        int len = LCS_FullDP::solve(s, s, lcs);
        REQUIRE(len == 26);
        REQUIRE(lcs == s);
    }
}

TEST_CASE("LCS_FullDP - 无公共子序列", "[LCS_FullDP]") {
    string lcs;

    SECTION("完全不同 abc / def") {
        int len = LCS_FullDP::solve("abc", "def", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs == "");
    }

    SECTION("单字符不同 a / b") {
        int len = LCS_FullDP::solve("a", "b", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs == "");
    }

    SECTION("长度差异大但无公共字符") {
        int len = LCS_FullDP::solve("abcde", "xyz", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs == "");
    }
}

TEST_CASE("LCS_FullDP - 空字符串情况", "[LCS_FullDP]") {
    string lcs;

    SECTION("text1 为空") {
        int len = LCS_FullDP::solve("", "abc", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs == "");
    }

    SECTION("text2 为空") {
        int len = LCS_FullDP::solve("abc", "", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs == "");
    }

    SECTION("两者均为空") {
        int len = LCS_FullDP::solve("", "", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs == "");
    }
}
