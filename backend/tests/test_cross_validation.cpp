#include "catch.hpp"
#include "../lcs/lcs_full_dp.h"
#include "../lcs/lcs_two_rows.h"
#include "../lcs/lcs_one_row.h"

TEST_CASE("三种实现结果一致性 - 正常场景", "[cross_validation]") {
    string lcs;

    SECTION("经典用例 abcde / ace") {
        int len1 = LCS_FullDP::solve("abcde", "ace", lcs);
        int len2 = LCS_TwoRows::solve("abcde", "ace");
        int len3 = LCS_OneRow::solve("abcde", "ace");
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
    }

    SECTION("部分匹配 oxcpqrsvwf / shmtulqrypy") {
        int len1 = LCS_FullDP::solve("oxcpqrsvwf", "shmtulqrypy", lcs);
        int len2 = LCS_TwoRows::solve("oxcpqrsvwf", "shmtulqrypy");
        int len3 = LCS_OneRow::solve("oxcpqrsvwf", "shmtulqrypy");
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
    }

    SECTION("单个公共字符 bsbininm / jmjkbkjkv") {
        int len1 = LCS_FullDP::solve("bsbininm", "jmjkbkjkv", lcs);
        int len2 = LCS_TwoRows::solve("bsbininm", "jmjkbkjkv");
        int len3 = LCS_OneRow::solve("bsbininm", "jmjkbkjkv");
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
    }

    SECTION("交错公共子序列 abac / cab") {
        int len1 = LCS_FullDP::solve("abac", "cab", lcs);
        int len2 = LCS_TwoRows::solve("abac", "cab");
        int len3 = LCS_OneRow::solve("abac", "cab");
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
    }
}

TEST_CASE("三种实现结果一致性 - 边界场景", "[cross_validation]") {
    string lcs;

    SECTION("两字符串完全相同 abc / abc") {
        int len1 = LCS_FullDP::solve("abc", "abc", lcs);
        int len2 = LCS_TwoRows::solve("abc", "abc");
        int len3 = LCS_OneRow::solve("abc", "abc");
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
    }

    SECTION("无公共子序列 abc / def") {
        int len1 = LCS_FullDP::solve("abc", "def", lcs);
        int len2 = LCS_TwoRows::solve("abc", "def");
        int len3 = LCS_OneRow::solve("abc", "def");
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
        REQUIRE(len1 == 0);
    }

    SECTION("text1 为空") {
        int len1 = LCS_FullDP::solve("", "abc", lcs);
        int len2 = LCS_TwoRows::solve("", "abc");
        int len3 = LCS_OneRow::solve("", "abc");
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
        REQUIRE(len1 == 0);
    }

    SECTION("text2 为空") {
        int len1 = LCS_FullDP::solve("abc", "", lcs);
        int len2 = LCS_TwoRows::solve("abc", "");
        int len3 = LCS_OneRow::solve("abc", "");
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
        REQUIRE(len1 == 0);
    }

    SECTION("两者均为空") {
        int len1 = LCS_FullDP::solve("", "", lcs);
        int len2 = LCS_TwoRows::solve("", "");
        int len3 = LCS_OneRow::solve("", "");
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
        REQUIRE(len1 == 0);
    }
}

TEST_CASE("三种实现结果一致性 - 参数交换对称性", "[cross_validation]") {
    SECTION("abcde / ace 交换后一致") {
        int len_fwd = LCS_TwoRows::solve("abcde", "ace");
        int len_rev = LCS_TwoRows::solve("ace", "abcde");
        REQUIRE(len_fwd == len_rev);

        len_fwd = LCS_OneRow::solve("abcde", "ace");
        len_rev = LCS_OneRow::solve("ace", "abcde");
        REQUIRE(len_fwd == len_rev);
    }

    SECTION("abac / cab 交换后一致") {
        int len_fwd = LCS_TwoRows::solve("abac", "cab");
        int len_rev = LCS_TwoRows::solve("cab", "abac");
        REQUIRE(len_fwd == len_rev);

        len_fwd = LCS_OneRow::solve("abac", "cab");
        len_rev = LCS_OneRow::solve("cab", "abac");
        REQUIRE(len_fwd == len_rev);
    }
}

TEST_CASE("三种实现结果一致性 - 多组随机用例", "[cross_validation]") {
    string lcs;

    vector<pair<string, string>> testCases = {
        {"abcde", "ace"},
        {"abc", "abc"},
        {"abc", "def"},
        {"oxcpqrsvwf", "shmtulqrypy"},
        {"bsbininm", "jmjkbkjkv"},
        {"abac", "cab"},
        {"", "abc"},
        {"abc", ""},
        {"", ""},
        {"a", "a"},
        {"a", "b"},
        {"abcdefghij", "acegj"},
        {"abc", "aebdc"},
        {"hello", "world"},
        {"algorithm", "altruistic"}
    };

    for (auto& tc : testCases) {
        int len1 = LCS_FullDP::solve(tc.first, tc.second, lcs);
        int len2 = LCS_TwoRows::solve(tc.first, tc.second);
        int len3 = LCS_OneRow::solve(tc.first, tc.second);
        INFO("text1=" << tc.first << ", text2=" << tc.second);
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
    }
}
