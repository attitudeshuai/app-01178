#include <gtest/gtest.h>
#include <string>

#include "../lcs_algorithms.h"
#include "../string_utils.h"

using namespace std;

TEST(LCS_FullDP_Test, NormalCase_HasCommonSubsequence) {
    string lcs;
    int len = LCS_FullDP::solve("abcde", "ace", lcs);
    EXPECT_EQ(len, 3);
    EXPECT_EQ(lcs, "ace");
}

TEST(LCS_FullDP_Test, NormalCase_LongerCommonSubsequence) {
    string lcs;
    int len = LCS_FullDP::solve("abcbdab", "bdcaba", lcs);
    EXPECT_EQ(len, 4);
    EXPECT_TRUE(lcs == "bcab" || lcs == "bdab");
}

TEST(LCS_FullDP_Test, Boundary_IdenticalStrings) {
    string lcs;
    int len = LCS_FullDP::solve("abc", "abc", lcs);
    EXPECT_EQ(len, 3);
    EXPECT_EQ(lcs, "abc");
}

TEST(LCS_FullDP_Test, Boundary_SingleCharSame) {
    string lcs;
    int len = LCS_FullDP::solve("a", "a", lcs);
    EXPECT_EQ(len, 1);
    EXPECT_EQ(lcs, "a");
}

TEST(LCS_FullDP_Test, Boundary_SingleCharDifferent) {
    string lcs;
    int len = LCS_FullDP::solve("a", "b", lcs);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(lcs, "");
}

TEST(LCS_FullDP_Test, NoCommonSubsequence) {
    string lcs;
    int len = LCS_FullDP::solve("abc", "def", lcs);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(lcs, "");
}

TEST(LCS_FullDP_Test, Empty_FirstStringEmpty) {
    string lcs;
    int len = LCS_FullDP::solve("", "abc", lcs);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(lcs, "");
}

TEST(LCS_FullDP_Test, Empty_SecondStringEmpty) {
    string lcs;
    int len = LCS_FullDP::solve("abc", "", lcs);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(lcs, "");
}

TEST(LCS_FullDP_Test, Empty_BothStringsEmpty) {
    string lcs;
    int len = LCS_FullDP::solve("", "", lcs);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(lcs, "");
}

TEST(LCS_FullDP_Test, SubsequenceAtBeginning) {
    string lcs;
    int len = LCS_FullDP::solve("abcdef", "abc", lcs);
    EXPECT_EQ(len, 3);
    EXPECT_EQ(lcs, "abc");
}

TEST(LCS_FullDP_Test, SubsequenceAtEnd) {
    string lcs;
    int len = LCS_FullDP::solve("abcdef", "def", lcs);
    EXPECT_EQ(len, 3);
    EXPECT_EQ(lcs, "def");
}

TEST(LCS_FullDP_Test, RepeatedCharacters) {
    string lcs;
    int len = LCS_FullDP::solve("aabba", "ababa", lcs);
    EXPECT_EQ(len, 4);
}

TEST(LCS_TwoRows_Test, NormalCase_HasCommonSubsequence) {
    int len = LCS_TwoRows::solve("abcde", "ace");
    EXPECT_EQ(len, 3);
}

TEST(LCS_TwoRows_Test, NormalCase_LongerCommonSubsequence) {
    int len = LCS_TwoRows::solve("abcbdab", "bdcaba");
    EXPECT_EQ(len, 4);
}

TEST(LCS_TwoRows_Test, Boundary_IdenticalStrings) {
    int len = LCS_TwoRows::solve("abc", "abc");
    EXPECT_EQ(len, 3);
}

TEST(LCS_TwoRows_Test, Boundary_SingleCharSame) {
    int len = LCS_TwoRows::solve("a", "a");
    EXPECT_EQ(len, 1);
}

TEST(LCS_TwoRows_Test, Boundary_SingleCharDifferent) {
    int len = LCS_TwoRows::solve("a", "b");
    EXPECT_EQ(len, 0);
}

TEST(LCS_TwoRows_Test, NoCommonSubsequence) {
    int len = LCS_TwoRows::solve("abc", "def");
    EXPECT_EQ(len, 0);
}

TEST(LCS_TwoRows_Test, Empty_FirstStringEmpty) {
    int len = LCS_TwoRows::solve("", "abc");
    EXPECT_EQ(len, 0);
}

TEST(LCS_TwoRows_Test, Empty_SecondStringEmpty) {
    int len = LCS_TwoRows::solve("abc", "");
    EXPECT_EQ(len, 0);
}

TEST(LCS_TwoRows_Test, Empty_BothStringsEmpty) {
    int len = LCS_TwoRows::solve("", "");
    EXPECT_EQ(len, 0);
}

TEST(LCS_TwoRows_Test, SubsequenceAtBeginning) {
    int len = LCS_TwoRows::solve("abcdef", "abc");
    EXPECT_EQ(len, 3);
}

TEST(LCS_TwoRows_Test, SubsequenceAtEnd) {
    int len = LCS_TwoRows::solve("abcdef", "def");
    EXPECT_EQ(len, 3);
}

TEST(LCS_TwoRows_Test, RepeatedCharacters) {
    int len = LCS_TwoRows::solve("aabba", "ababa");
    EXPECT_EQ(len, 4);
}

TEST(LCS_TwoRows_Test, FirstShorterThanSecond) {
    int len = LCS_TwoRows::solve("ace", "abcde");
    EXPECT_EQ(len, 3);
}

TEST(LCS_OneRow_Test, NormalCase_HasCommonSubsequence) {
    int len = LCS_OneRow::solve("abcde", "ace");
    EXPECT_EQ(len, 3);
}

TEST(LCS_OneRow_Test, NormalCase_LongerCommonSubsequence) {
    int len = LCS_OneRow::solve("abcbdab", "bdcaba");
    EXPECT_EQ(len, 4);
}

TEST(LCS_OneRow_Test, Boundary_IdenticalStrings) {
    int len = LCS_OneRow::solve("abc", "abc");
    EXPECT_EQ(len, 3);
}

TEST(LCS_OneRow_Test, Boundary_SingleCharSame) {
    int len = LCS_OneRow::solve("a", "a");
    EXPECT_EQ(len, 1);
}

TEST(LCS_OneRow_Test, Boundary_SingleCharDifferent) {
    int len = LCS_OneRow::solve("a", "b");
    EXPECT_EQ(len, 0);
}

TEST(LCS_OneRow_Test, NoCommonSubsequence) {
    int len = LCS_OneRow::solve("abc", "def");
    EXPECT_EQ(len, 0);
}

TEST(LCS_OneRow_Test, Empty_FirstStringEmpty) {
    int len = LCS_OneRow::solve("", "abc");
    EXPECT_EQ(len, 0);
}

TEST(LCS_OneRow_Test, Empty_SecondStringEmpty) {
    int len = LCS_OneRow::solve("abc", "");
    EXPECT_EQ(len, 0);
}

TEST(LCS_OneRow_Test, Empty_BothStringsEmpty) {
    int len = LCS_OneRow::solve("", "");
    EXPECT_EQ(len, 0);
}

TEST(LCS_OneRow_Test, SubsequenceAtBeginning) {
    int len = LCS_OneRow::solve("abcdef", "abc");
    EXPECT_EQ(len, 3);
}

TEST(LCS_OneRow_Test, SubsequenceAtEnd) {
    int len = LCS_OneRow::solve("abcdef", "def");
    EXPECT_EQ(len, 3);
}

TEST(LCS_OneRow_Test, RepeatedCharacters) {
    int len = LCS_OneRow::solve("aabba", "ababa");
    EXPECT_EQ(len, 4);
}

TEST(LCS_OneRow_Test, FirstShorterThanSecond) {
    int len = LCS_OneRow::solve("ace", "abcde");
    EXPECT_EQ(len, 3);
}

TEST(CrossValidation_Test, NormalCases_ThreeMethodsConsistent) {
    string testCases[][2] = {
        {"abcde", "ace"},
        {"abcbdab", "bdcaba"},
        {"oxcpqrsvwf", "shmtulqrypy"},
        {"bsbininm", "jmjkbkjkv"},
        {"abc", "abc"},
        {"abc", "def"},
        {"a", "a"},
        {"a", "b"},
        {"aabba", "ababa"},
        {"abcdef", "abc"},
        {"abcdef", "def"},
    };
    
    for (auto& tc : testCases) {
        string lcs;
        int len1 = LCS_FullDP::solve(tc[0], tc[1], lcs);
        int len2 = LCS_TwoRows::solve(tc[0], tc[1]);
        int len3 = LCS_OneRow::solve(tc[0], tc[1]);
        
        EXPECT_EQ(len1, len2) << "Mismatch for: " << tc[0] << ", " << tc[1];
        EXPECT_EQ(len2, len3) << "Mismatch for: " << tc[0] << ", " << tc[1];
    }
}

TEST(CrossValidation_Test, EmptyCases_ThreeMethodsConsistent) {
    string testCases[][2] = {
        {"", "abc"},
        {"abc", ""},
        {"", ""},
    };
    
    for (auto& tc : testCases) {
        string lcs;
        int len1 = LCS_FullDP::solve(tc[0], tc[1], lcs);
        int len2 = LCS_TwoRows::solve(tc[0], tc[1]);
        int len3 = LCS_OneRow::solve(tc[0], tc[1]);
        
        EXPECT_EQ(len1, len2) << "Mismatch for: \"" << tc[0] << "\", \"" << tc[1] << "\"";
        EXPECT_EQ(len2, len3) << "Mismatch for: \"" << tc[0] << "\", \"" << tc[1] << "\"";
        EXPECT_EQ(len1, 0);
    }
}

TEST(CrossValidation_Test, ReversedInputs_ThreeMethodsConsistent) {
    string testCases[][2] = {
        {"abcde", "ace"},
        {"abcbdab", "bdcaba"},
        {"abc", "def"},
    };
    
    for (auto& tc : testCases) {
        string lcs1, lcs2;
        int len1_forward = LCS_FullDP::solve(tc[0], tc[1], lcs1);
        int len1_reverse = LCS_FullDP::solve(tc[1], tc[0], lcs2);
        int len2_forward = LCS_TwoRows::solve(tc[0], tc[1]);
        int len2_reverse = LCS_TwoRows::solve(tc[1], tc[0]);
        int len3_forward = LCS_OneRow::solve(tc[0], tc[1]);
        int len3_reverse = LCS_OneRow::solve(tc[1], tc[0]);
        
        EXPECT_EQ(len1_forward, len1_reverse);
        EXPECT_EQ(len2_forward, len2_reverse);
        EXPECT_EQ(len3_forward, len3_reverse);
    }
}

TEST(IsValidInput_Test, Valid_LowercaseLetters) {
    EXPECT_TRUE(isValidInput("abc"));
    EXPECT_TRUE(isValidInput("abcdefghijklmnopqrstuvwxyz"));
    EXPECT_TRUE(isValidInput("a"));
}

TEST(IsValidInput_Test, Valid_EmptyString) {
    EXPECT_TRUE(isValidInput(""));
}

TEST(IsValidInput_Test, Invalid_UppercaseLetters) {
    EXPECT_FALSE(isValidInput("Abc"));
    EXPECT_FALSE(isValidInput("ABC"));
    EXPECT_FALSE(isValidInput("abcD"));
}

TEST(IsValidInput_Test, Invalid_Digits) {
    EXPECT_FALSE(isValidInput("abc123"));
    EXPECT_FALSE(isValidInput("123"));
    EXPECT_FALSE(isValidInput("a1b"));
}

TEST(IsValidInput_Test, Invalid_SpecialCharacters) {
    EXPECT_FALSE(isValidInput("abc!"));
    EXPECT_FALSE(isValidInput("a b"));
    EXPECT_FALSE(isValidInput("a_b"));
    EXPECT_FALSE(isValidInput("a-b"));
    EXPECT_FALSE(isValidInput("a.b"));
}

TEST(IsValidInput_Test, Invalid_Spaces) {
    EXPECT_FALSE(isValidInput(" "));
    EXPECT_FALSE(isValidInput("abc "));
    EXPECT_FALSE(isValidInput(" abc"));
}

TEST(IsValidInput_Test, Invalid_NewlineAndTab) {
    EXPECT_FALSE(isValidInput(string("\n", 1)));
    EXPECT_FALSE(isValidInput(string("\t", 1)));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
