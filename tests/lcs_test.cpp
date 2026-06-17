#include <gtest/gtest.h>
#include <string>
#include "../backend/lcs.h"

using namespace std;

// ============================================================
// LCS_FullDP 测试套件
// ============================================================

TEST(LCS_FullDP_Test, NormalCase_CommonSubsequenceExists) {
    string lcs;
    int len = LCS_FullDP::solve("abcde", "ace", lcs);
    EXPECT_EQ(len, 3);
    EXPECT_EQ(lcs, "ace");
}

TEST(LCS_FullDP_Test, NormalCase_LongerCommonSubsequence) {
    string lcs;
    int len = LCS_FullDP::solve("abcbdab", "bdcaba", lcs);
    EXPECT_EQ(len, 4);
    ASSERT_EQ(lcs.length(), static_cast<size_t>(len));

    size_t i = 0, j = 0;
    while (i < lcs.length() && j < string("abcbdab").length()) {
        if (lcs[i] == string("abcbdab")[j]) i++;
        j++;
    }
    EXPECT_EQ(i, lcs.length()) << "LCS is not a subsequence of text1";

    i = 0; j = 0;
    while (i < lcs.length() && j < string("bdcaba").length()) {
        if (lcs[i] == string("bdcaba")[j]) i++;
        j++;
    }
    EXPECT_EQ(i, lcs.length()) << "LCS is not a subsequence of text2";
}

TEST(LCS_FullDP_Test, Boundary_BothStringsIdentical) {
    string lcs;
    int len = LCS_FullDP::solve("abc", "abc", lcs);
    EXPECT_EQ(len, 3);
    EXPECT_EQ(lcs, "abc");
}

TEST(LCS_FullDP_Test, Boundary_SingleCharIdentical) {
    string lcs;
    int len = LCS_FullDP::solve("a", "a", lcs);
    EXPECT_EQ(len, 1);
    EXPECT_EQ(lcs, "a");
}

TEST(LCS_FullDP_Test, NoCommonSubsequence_CompletelyDifferent) {
    string lcs;
    int len = LCS_FullDP::solve("abc", "def", lcs);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(lcs, "");
}

TEST(LCS_FullDP_Test, NoCommonSubsequence_SingleCharDifferent) {
    string lcs;
    int len = LCS_FullDP::solve("a", "b", lcs);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(lcs, "");
}

TEST(LCS_FullDP_Test, EmptyString_FirstEmpty) {
    string lcs;
    int len = LCS_FullDP::solve("", "abc", lcs);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(lcs, "");
}

TEST(LCS_FullDP_Test, EmptyString_SecondEmpty) {
    string lcs;
    int len = LCS_FullDP::solve("abc", "", lcs);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(lcs, "");
}

TEST(LCS_FullDP_Test, EmptyString_BothEmpty) {
    string lcs;
    int len = LCS_FullDP::solve("", "", lcs);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(lcs, "");
}

TEST(LCS_FullDP_Test, PartialOverlap_CommonAtBeginning) {
    string lcs;
    int len = LCS_FullDP::solve("abcd", "abxyz", lcs);
    EXPECT_EQ(len, 2);
    EXPECT_EQ(lcs, "ab");
}

TEST(LCS_FullDP_Test, PartialOverlap_CommonAtEnd) {
    string lcs;
    int len = LCS_FullDP::solve("xyzcd", "abcd", lcs);
    EXPECT_EQ(len, 2);
    EXPECT_EQ(lcs, "cd");
}

TEST(LCS_FullDP_Test, PartialOverlap_ScatteredChars) {
    string lcs;
    int len = LCS_FullDP::solve("oxcpqrsvwf", "shmtulqrypy", lcs);
    EXPECT_EQ(len, 2);
}

TEST(LCS_FullDP_Test, LengthOneDifference) {
    string lcs;
    int len = LCS_FullDP::solve("bsbininm", "jmjkbkjkv", lcs);
    EXPECT_EQ(len, 1);
}

TEST(LCS_FullDP_Test, ReversedStrings) {
    string lcs;
    int len = LCS_FullDP::solve("abcde", "edcba", lcs);
    EXPECT_EQ(len, 1);
}

TEST(LCS_FullDP_Test, OneCharLonger) {
    string lcs;
    int len = LCS_FullDP::solve("aaaaa", "a", lcs);
    EXPECT_EQ(len, 1);
    EXPECT_EQ(lcs, "a");
}

TEST(LCS_FullDP_Test, AllSameChars) {
    string lcs;
    int len = LCS_FullDP::solve("aaaaa", "aaaaa", lcs);
    EXPECT_EQ(len, 5);
    EXPECT_EQ(lcs, "aaaaa");
}

// ============================================================
// LCS_TwoRows 测试套件
// ============================================================

TEST(LCS_TwoRows_Test, NormalCase_CommonSubsequenceExists) {
    int len = LCS_TwoRows::solve("abcde", "ace");
    EXPECT_EQ(len, 3);
}

TEST(LCS_TwoRows_Test, Boundary_BothStringsIdentical) {
    int len = LCS_TwoRows::solve("abc", "abc");
    EXPECT_EQ(len, 3);
}

TEST(LCS_TwoRows_Test, NoCommonSubsequence_CompletelyDifferent) {
    int len = LCS_TwoRows::solve("abc", "def");
    EXPECT_EQ(len, 0);
}

TEST(LCS_TwoRows_Test, EmptyString_FirstEmpty) {
    int len = LCS_TwoRows::solve("", "abc");
    EXPECT_EQ(len, 0);
}

TEST(LCS_TwoRows_Test, EmptyString_SecondEmpty) {
    int len = LCS_TwoRows::solve("abc", "");
    EXPECT_EQ(len, 0);
}

TEST(LCS_TwoRows_Test, EmptyString_BothEmpty) {
    int len = LCS_TwoRows::solve("", "");
    EXPECT_EQ(len, 0);
}

TEST(LCS_TwoRows_Test, PartialOverlap_ScatteredChars) {
    int len = LCS_TwoRows::solve("oxcpqrsvwf", "shmtulqrypy");
    EXPECT_EQ(len, 2);
}

TEST(LCS_TwoRows_Test, LengthOneDifference) {
    int len = LCS_TwoRows::solve("bsbininm", "jmjkbkjkv");
    EXPECT_EQ(len, 1);
}

TEST(LCS_TwoRows_Test, ReversedStrings) {
    int len = LCS_TwoRows::solve("abcde", "edcba");
    EXPECT_EQ(len, 1);
}

TEST(LCS_TwoRows_Test, AllSameChars) {
    int len = LCS_TwoRows::solve("aaaaa", "aaaaa");
    EXPECT_EQ(len, 5);
}

TEST(LCS_TwoRows_Test, UnequalLengths_FirstLonger) {
    int len = LCS_TwoRows::solve("abcdefghij", "ace");
    EXPECT_EQ(len, 3);
}

TEST(LCS_TwoRows_Test, UnequalLengths_SecondLonger) {
    int len = LCS_TwoRows::solve("ace", "abcdefghij");
    EXPECT_EQ(len, 3);
}

TEST(LCS_TwoRows_Test, SingleCharIdentical) {
    int len = LCS_TwoRows::solve("a", "a");
    EXPECT_EQ(len, 1);
}

TEST(LCS_TwoRows_Test, SingleCharDifferent) {
    int len = LCS_TwoRows::solve("a", "b");
    EXPECT_EQ(len, 0);
}

// ============================================================
// LCS_OneRow 测试套件
// ============================================================

TEST(LCS_OneRow_Test, NormalCase_CommonSubsequenceExists) {
    int len = LCS_OneRow::solve("abcde", "ace");
    EXPECT_EQ(len, 3);
}

TEST(LCS_OneRow_Test, Boundary_BothStringsIdentical) {
    int len = LCS_OneRow::solve("abc", "abc");
    EXPECT_EQ(len, 3);
}

TEST(LCS_OneRow_Test, NoCommonSubsequence_CompletelyDifferent) {
    int len = LCS_OneRow::solve("abc", "def");
    EXPECT_EQ(len, 0);
}

TEST(LCS_OneRow_Test, EmptyString_FirstEmpty) {
    int len = LCS_OneRow::solve("", "abc");
    EXPECT_EQ(len, 0);
}

TEST(LCS_OneRow_Test, EmptyString_SecondEmpty) {
    int len = LCS_OneRow::solve("abc", "");
    EXPECT_EQ(len, 0);
}

TEST(LCS_OneRow_Test, EmptyString_BothEmpty) {
    int len = LCS_OneRow::solve("", "");
    EXPECT_EQ(len, 0);
}

TEST(LCS_OneRow_Test, PartialOverlap_ScatteredChars) {
    int len = LCS_OneRow::solve("oxcpqrsvwf", "shmtulqrypy");
    EXPECT_EQ(len, 2);
}

TEST(LCS_OneRow_Test, LengthOneDifference) {
    int len = LCS_OneRow::solve("bsbininm", "jmjkbkjkv");
    EXPECT_EQ(len, 1);
}

TEST(LCS_OneRow_Test, ReversedStrings) {
    int len = LCS_OneRow::solve("abcde", "edcba");
    EXPECT_EQ(len, 1);
}

TEST(LCS_OneRow_Test, AllSameChars) {
    int len = LCS_OneRow::solve("aaaaa", "aaaaa");
    EXPECT_EQ(len, 5);
}

TEST(LCS_OneRow_Test, UnequalLengths_FirstLonger) {
    int len = LCS_OneRow::solve("abcdefghij", "ace");
    EXPECT_EQ(len, 3);
}

TEST(LCS_OneRow_Test, UnequalLengths_SecondLonger) {
    int len = LCS_OneRow::solve("ace", "abcdefghij");
    EXPECT_EQ(len, 3);
}

TEST(LCS_OneRow_Test, SingleCharIdentical) {
    int len = LCS_OneRow::solve("a", "a");
    EXPECT_EQ(len, 1);
}

TEST(LCS_OneRow_Test, SingleCharDifferent) {
    int len = LCS_OneRow::solve("a", "b");
    EXPECT_EQ(len, 0);
}

// ============================================================
// isValidInput 输入校验测试套件
// ============================================================

TEST(IsValidInput_Test, ValidInput_AllLowercaseLetters) {
    EXPECT_TRUE(isValidInput("abc"));
    EXPECT_TRUE(isValidInput("xyz"));
    EXPECT_TRUE(isValidInput("abcdefghijklmnopqrstuvwxyz"));
}

TEST(IsValidInput_Test, ValidInput_SingleLowercaseLetter) {
    EXPECT_TRUE(isValidInput("a"));
    EXPECT_TRUE(isValidInput("z"));
}

TEST(IsValidInput_Test, ValidInput_EmptyString) {
    EXPECT_TRUE(isValidInput(""));
}

TEST(IsValidInput_Test, InvalidInput_UppercaseLetters) {
    EXPECT_FALSE(isValidInput("Abc"));
    EXPECT_FALSE(isValidInput("ABC"));
    EXPECT_FALSE(isValidInput("aBc"));
}

TEST(IsValidInput_Test, InvalidInput_Digits) {
    EXPECT_FALSE(isValidInput("abc123"));
    EXPECT_FALSE(isValidInput("123"));
    EXPECT_FALSE(isValidInput("a1b"));
}

TEST(IsValidInput_Test, InvalidInput_SpecialCharacters) {
    EXPECT_FALSE(isValidInput("abc!"));
    EXPECT_FALSE(isValidInput("a b"));
    EXPECT_FALSE(isValidInput("a-b"));
    EXPECT_FALSE(isValidInput("a_b"));
    EXPECT_FALSE(isValidInput("a.b"));
    EXPECT_FALSE(isValidInput("@"));
    EXPECT_FALSE(isValidInput("#"));
    EXPECT_FALSE(isValidInput("$"));
}

TEST(IsValidInput_Test, InvalidInput_Spaces) {
    EXPECT_FALSE(isValidInput(" "));
    EXPECT_FALSE(isValidInput("abc def"));
}

TEST(IsValidInput_Test, InvalidInput_NewlineAndTab) {
    EXPECT_FALSE(isValidInput(string("a\nb", 3)));
    EXPECT_FALSE(isValidInput(string("a\tb", 3)));
}

// ============================================================
// 三种实现结果一致性交叉验证测试套件
// ============================================================

TEST(LCS_Consistency_Test, NormalCases_AllThreeAgree) {
    struct TestCase {
        string text1;
        string text2;
    };

    TestCase cases[] = {
        {"abcde", "ace"},
        {"abc", "abc"},
        {"abc", "def"},
        {"oxcpqrsvwf", "shmtulqrypy"},
        {"bsbininm", "jmjkbkjkv"},
        {"abcbdab", "bdcaba"},
        {"abcd", "abxyz"},
        {"xyzcd", "abcd"},
        {"abcde", "edcba"},
        {"aaaaa", "a"},
        {"aaaaa", "aaaaa"},
        {"abcdefghij", "ace"},
        {"ace", "abcdefghij"},
    };

    for (const auto& tc : cases) {
        string lcs;
        int len_full = LCS_FullDP::solve(tc.text1, tc.text2, lcs);
        int len_two = LCS_TwoRows::solve(tc.text1, tc.text2);
        int len_one = LCS_OneRow::solve(tc.text1, tc.text2);

        EXPECT_EQ(len_full, len_two)
            << "text1=\"" << tc.text1 << "\", text2=\"" << tc.text2 << "\""
            << ": LCS_FullDP=" << len_full << ", LCS_TwoRows=" << len_two;
        EXPECT_EQ(len_two, len_one)
            << "text1=\"" << tc.text1 << "\", text2=\"" << tc.text2 << "\""
            << ": LCS_TwoRows=" << len_two << ", LCS_OneRow=" << len_one;
    }
}

TEST(LCS_Consistency_Test, EmptyStringCases_AllThreeAgree) {
    struct TestCase {
        string text1;
        string text2;
    };

    TestCase cases[] = {
        {"", "abc"},
        {"abc", ""},
        {"", ""},
        {"", "a"},
        {"a", ""},
    };

    for (const auto& tc : cases) {
        string lcs;
        int len_full = LCS_FullDP::solve(tc.text1, tc.text2, lcs);
        int len_two = LCS_TwoRows::solve(tc.text1, tc.text2);
        int len_one = LCS_OneRow::solve(tc.text1, tc.text2);

        EXPECT_EQ(len_full, 0);
        EXPECT_EQ(len_two, 0);
        EXPECT_EQ(len_one, 0);
    }
}

TEST(LCS_Consistency_Test, SingleCharCases_AllThreeAgree) {
    for (char c1 = 'a'; c1 <= 'z'; c1++) {
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            string s1(1, c1);
            string s2(1, c2);

            string lcs;
            int len_full = LCS_FullDP::solve(s1, s2, lcs);
            int len_two = LCS_TwoRows::solve(s1, s2);
            int len_one = LCS_OneRow::solve(s1, s2);

            int expected = (c1 == c2) ? 1 : 0;
            EXPECT_EQ(len_full, expected) << "s1=\"" << s1 << "\", s2=\"" << s2 << "\"";
            EXPECT_EQ(len_two, expected) << "s1=\"" << s1 << "\", s2=\"" << s2 << "\"";
            EXPECT_EQ(len_one, expected) << "s1=\"" << s1 << "\", s2=\"" << s2 << "\"";
            EXPECT_EQ(len_full, len_two);
            EXPECT_EQ(len_two, len_one);
        }
    }
}

TEST(LCS_Consistency_Test, SwappedArguments_AllThreeAgree) {
    struct TestCase {
        string text1;
        string text2;
    };

    TestCase cases[] = {
        {"abcde", "ace"},
        {"abc", "def"},
        {"oxcpqrsvwf", "shmtulqrypy"},
        {"bsbininm", "jmjkbkjkv"},
    };

    for (const auto& tc : cases) {
        string lcs1, lcs2;
        int len_full_fwd = LCS_FullDP::solve(tc.text1, tc.text2, lcs1);
        int len_full_rev = LCS_FullDP::solve(tc.text2, tc.text1, lcs2);
        int len_two_fwd = LCS_TwoRows::solve(tc.text1, tc.text2);
        int len_two_rev = LCS_TwoRows::solve(tc.text2, tc.text1);
        int len_one_fwd = LCS_OneRow::solve(tc.text1, tc.text2);
        int len_one_rev = LCS_OneRow::solve(tc.text2, tc.text1);

        EXPECT_EQ(len_full_fwd, len_full_rev);
        EXPECT_EQ(len_two_fwd, len_two_rev);
        EXPECT_EQ(len_one_fwd, len_one_rev);
    }
}

TEST(LCS_Consistency_Test, FullDP_LcsStringIsValidSubsequence) {
    struct TestCase {
        string text1;
        string text2;
        int expectedLen;
    };

    TestCase cases[] = {
        {"abcde", "ace", 3},
        {"abc", "abc", 3},
        {"abcbdab", "bdcaba", 4},
        {"oxcpqrsvwf", "shmtulqrypy", 2},
    };

    for (const auto& tc : cases) {
        string lcs;
        int len = LCS_FullDP::solve(tc.text1, tc.text2, lcs);

        EXPECT_EQ(len, tc.expectedLen);
        ASSERT_EQ(lcs.length(), static_cast<size_t>(len));

        size_t i = 0, j = 0;
        while (i < lcs.length() && j < tc.text1.length()) {
            if (lcs[i] == tc.text1[j]) {
                i++;
            }
            j++;
        }
        EXPECT_EQ(i, lcs.length()) << "LCS is not a subsequence of text1";

        i = 0;
        j = 0;
        while (i < lcs.length() && j < tc.text2.length()) {
            if (lcs[i] == tc.text2[j]) {
                i++;
            }
            j++;
        }
        EXPECT_EQ(i, lcs.length()) << "LCS is not a subsequence of text2";
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
