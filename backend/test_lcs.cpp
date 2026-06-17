/**
 * 最长公共子序列 (LCS) 算法单元测试
 *
 * 测试框架：Catch2 v2.13.10
 * 覆盖场景：
 *   1. 正常情况：两个字符串存在公共子序列
 *   2. 边界情况：两个字符串完全相同
 *   3. 无公共子序列的情况
 *   4. 空字符串情况
 *   5. 非法字符容错处理
 *   6. 三种实现结果一致性交叉验证
 *
 * 编译运行：
 *   g++ -o test_lcs test_lcs.cpp -std=c++11 -O2
 *   ./test_lcs
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "lcs.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;


// ============================================================
// 场景一：正常情况 —— 两个字符串存在公共子序列
// ============================================================
TEST_CASE("正常情况：两个字符串存在公共子序列", "[LCS][Normal]") {
    SECTION("abcde 与 ace 的 LCS 长度为 3，序列为 ace") {
        string lcs;
        int len = LCS_FullDP::solve("abcde", "ace", lcs);
        REQUIRE(len == 3);
        REQUIRE(lcs == "ace");
    }

    SECTION("oxcpqrsvwf 与 shmtulqrypy 的 LCS 长度为 2，序列为 qr") {
        string lcs;
        int len = LCS_FullDP::solve("oxcpqrsvwf", "shmtulqrypy", lcs);
        REQUIRE(len == 2);
        REQUIRE(lcs == "qr");
    }

    SECTION("bsbininm 与 jmjkbkjkv 的 LCS 长度为 1（存在多个等长解，仅校验长度）") {
        string lcs;
        int len = LCS_FullDP::solve("bsbininm", "jmjkbkjkv", lcs);
        REQUIRE(len == 1);
        REQUIRE(lcs.size() == 1);
    }

    SECTION("后缀匹配：abcde 与 cde 的 LCS 长度为 3，序列为 cde") {
        string lcs;
        int len = LCS_FullDP::solve("abcde", "cde", lcs);
        REQUIRE(len == 3);
        REQUIRE(lcs == "cde");
    }

    SECTION("前缀匹配：abcde 与 abc 的 LCS 长度为 3，序列为 abc") {
        string lcs;
        int len = LCS_FullDP::solve("abcde", "abc", lcs);
        REQUIRE(len == 3);
        REQUIRE(lcs == "abc");
    }

    SECTION("交错匹配：abcde 与 bcd 的 LCS 长度为 3，序列为 bcd") {
        string lcs;
        int len = LCS_FullDP::solve("abcde", "bcd", lcs);
        REQUIRE(len == 3);
        REQUIRE(lcs == "bcd");
    }
}


// ============================================================
// 场景二：边界情况 —— 两个字符串完全相同
// ============================================================
TEST_CASE("边界情况：两个字符串完全相同", "[LCS][Boundary]") {
    SECTION("相同字符串 abc 的 LCS 为 abc，长度 3") {
        string lcs;
        int len = LCS_FullDP::solve("abc", "abc", lcs);
        REQUIRE(len == 3);
        REQUIRE(lcs == "abc");
    }

    SECTION("相同单字符 x 的 LCS 为 x，长度 1") {
        string lcs;
        int len = LCS_FullDP::solve("x", "x", lcs);
        REQUIRE(len == 1);
        REQUIRE(lcs == "x");
    }

    SECTION("相同长字符串的 LCS 等于自身") {
        string s = "abcdefghij";
        string lcs;
        int len = LCS_FullDP::solve(s, s, lcs);
        REQUIRE(len == static_cast<int>(s.size()));
        REQUIRE(lcs == s);
    }

    SECTION("完全相同时三种实现长度一致") {
        string s = "abcabc";
        string lcs;
        int len1 = LCS_FullDP::solve(s, s, lcs);
        int len2 = LCS_TwoRows::solve(s, s);
        int len3 = LCS_OneRow::solve(s, s);
        REQUIRE(len1 == 6);
        REQUIRE(len1 == len2);
        REQUIRE(len2 == len3);
    }
}


// ============================================================
// 场景三：完全没有公共子序列
// ============================================================
TEST_CASE("无公共子序列的情况", "[LCS][None]") {
    SECTION("abc 与 def 无公共子序列，长度 0") {
        string lcs;
        int len = LCS_FullDP::solve("abc", "def", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs.empty());
    }

    SECTION("a 与 z 无公共子序列，长度 0") {
        string lcs;
        int len = LCS_FullDP::solve("a", "z", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs.empty());
    }

    SECTION("无公共子序列时三种实现均返回 0") {
        REQUIRE(LCS_TwoRows::solve("abc", "def") == 0);
        REQUIRE(LCS_OneRow::solve("abc", "def") == 0);
        REQUIRE(LCS_TwoRows::solve("a", "z") == 0);
        REQUIRE(LCS_OneRow::solve("a", "z") == 0);
    }
}


// ============================================================
// 场景四：空字符串情况
// ============================================================
TEST_CASE("空字符串情况", "[LCS][Empty]") {
    SECTION("两个字符串均为空") {
        string lcs;
        int len = LCS_FullDP::solve("", "", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs.empty());
    }

    SECTION("text1 为空，text2 非空") {
        string lcs;
        int len = LCS_FullDP::solve("", "abc", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs.empty());
    }

    SECTION("text2 为空，text1 非空") {
        string lcs;
        int len = LCS_FullDP::solve("abc", "", lcs);
        REQUIRE(len == 0);
        REQUIRE(lcs.empty());
    }

    SECTION("空字符串对三种实现均返回 0") {
        REQUIRE(LCS_TwoRows::solve("", "") == 0);
        REQUIRE(LCS_OneRow::solve("", "") == 0);
        REQUIRE(LCS_TwoRows::solve("", "abc") == 0);
        REQUIRE(LCS_OneRow::solve("abc", "") == 0);
        REQUIRE(LCS_TwoRows::solve("abc", "") == 0);
        REQUIRE(LCS_OneRow::solve("", "abc") == 0);
    }
}


// ============================================================
// 场景五：非法字符容错处理
// ============================================================
TEST_CASE("非法字符容错处理", "[LCS][Invalid]") {
    SECTION("isValidInput 对合法小写字母返回 true") {
        REQUIRE(isValidInput("abc") == true);
        REQUIRE(isValidInput("a") == true);
        REQUIRE(isValidInput("") == true);
        REQUIRE(isValidInput("abcdefghijklmnopqrstuvwxyz") == true);
    }

    SECTION("isValidInput 对大写字母返回 false") {
        REQUIRE(isValidInput("ABC") == false);
        REQUIRE(isValidInput("Abc") == false);
        REQUIRE(isValidInput("abC") == false);
    }

    SECTION("isValidInput 对数字返回 false") {
        REQUIRE(isValidInput("abc123") == false);
        REQUIRE(isValidInput("123") == false);
        REQUIRE(isValidInput("a1") == false);
    }

    SECTION("isValidInput 对空格与特殊字符返回 false") {
        REQUIRE(isValidInput("ab c") == false);
        REQUIRE(isValidInput("ab,c") == false);
        REQUIRE(isValidInput("ab@c") == false);
        REQUIRE(isValidInput("ab-c") == false);
        REQUIRE(isValidInput("ab.c") == false);
    }

    SECTION("算法对非法字符不崩溃且能正常计算（容错）") {
        // 算法本身不做字符校验，应能处理任意字符而不抛异常
        string lcs;
        REQUIRE_NOTHROW(LCS_FullDP::solve("Ab1", "Ab1", lcs));
        REQUIRE(lcs == "Ab1");

        REQUIRE_NOTHROW(LCS_TwoRows::solve("Ab1", "Ab1"));
        REQUIRE_NOTHROW(LCS_OneRow::solve("Ab1", "Ab1"));

        // 含空格与符号的字符串同样可被处理
        string lcs2;
        REQUIRE_NOTHROW(LCS_FullDP::solve("a b", "a b", lcs2));
        REQUIRE(lcs2 == "a b");
    }
}


// ============================================================
// 场景六：三种实现结果一致性交叉验证
// ============================================================
TEST_CASE("三种实现结果一致性交叉验证", "[LCS][Consistency]") {
    struct TestCase {
        string text1;
        string text2;
        int expected;
    };

    vector<TestCase> cases = {
        {"abcde",            "ace",               3},
        {"abc",              "abc",               3},
        {"abc",              "def",               0},
        {"oxcpqrsvwf",       "shmtulqrypy",       2},
        {"bsbininm",         "jmjkbkjkv",         1},
        {"",                 "",                  0},
        {"abc",              "",                  0},
        {"",                 "abc",               0},
        {"a",                "a",                 1},
        {"a",                "b",                 0},
        {"abcdef",           "abcdef",            6},
        {"abc",              "cba",               1},
        {"pmjghexyvonrggmytwz", "ulqwyq",         1},
        {"aaaa",             "aa",                2},
        {"abcde",            "edcba",             1},
        {"xyz",              "zyx",               1},
        {"abcabc",           "abc",               3},
        {"abcbdab",          "bdcaba",            4},
    };

    for (const auto& tc : cases) {
        SECTION("输入 \"" + tc.text1 + "\" 与 \"" + tc.text2 +
                "\" 三种方法结果一致且为 " + to_string(tc.expected)) {
            string lcs;
            int len1 = LCS_FullDP::solve(tc.text1, tc.text2, lcs);
            int len2 = LCS_TwoRows::solve(tc.text1, tc.text2);
            int len3 = LCS_OneRow::solve(tc.text1, tc.text2);

            REQUIRE(len1 == tc.expected);
            REQUIRE(len2 == tc.expected);
            REQUIRE(len3 == tc.expected);
            REQUIRE(len1 == len2);
            REQUIRE(len2 == len3);
        }
    }

    SECTION("随机字符串压力测试：三种方法结果一致") {
        srand(42);
        for (int t = 0; t < 300; t++) {
            int len1 = rand() % 25;
            int len2 = rand() % 25;
            string s1, s2;
            for (int i = 0; i < len1; i++) s1 += static_cast<char>('a' + rand() % 26);
            for (int i = 0; i < len2; i++) s2 += static_cast<char>('a' + rand() % 26);

            string lcs;
            int r1 = LCS_FullDP::solve(s1, s2, lcs);
            int r2 = LCS_TwoRows::solve(s1, s2);
            int r3 = LCS_OneRow::solve(s1, s2);
            REQUIRE(r1 == r2);
            REQUIRE(r2 == r3);
        }
    }
}
