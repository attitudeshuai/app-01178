/**
 * LCS 算法测试程序
 *
 * 重点覆盖：
 * 1. 三种实现结果是否一致
 * 2. 空字符串、完全无交集、完全相同等边界情况
 * 3. 方法一回溯的LCS字符串正确性验证
 */

#include <iostream>
#include <string>
#include <vector>

#include "lcs.h"

using namespace std;

int totalTests = 0;
int passedTests = 0;

bool isSubsequence(const string& sub, const string& str) {
    int si = 0;
    for (int i = 0; i < (int)str.length() && si < (int)sub.length(); i++) {
        if (sub[si] == str[i]) {
            si++;
        }
    }
    return si == (int)sub.length();
}

void runTest(const string& name, const string& text1, const string& text2, int expectedLen) {
    totalTests++;
    cout << "\n[TEST " << totalTests << "] " << name << endl;
    cout << "  text1 = \"" << text1 << "\" (长度: " << text1.length() << ")" << endl;
    cout << "  text2 = \"" << text2 << "\" (长度: " << text2.length() << ")" << endl;

    string lcsString;
    int len1 = LCS_FullDP::solve(text1, text2, lcsString);
    int len2 = LCS_TwoRows::solve(text1, text2);
    int len3 = LCS_OneRow::solve(text1, text2);

    bool consistent = (len1 == len2 && len2 == len3);
    bool lenCorrect = (expectedLen < 0 || len1 == expectedLen);
    bool lcsValid = (len1 == 0) ? (lcsString == "") :
                    ((int)lcsString.length() == len1 &&
                     isSubsequence(lcsString, text1) &&
                     isSubsequence(lcsString, text2));

    bool allPassed = consistent && lenCorrect && lcsValid;

    cout << "  方法一: " << len1;
    if (len1 > 0) cout << " (LCS: \"" << lcsString << "\")";
    cout << endl;
    cout << "  方法二: " << len2 << endl;
    cout << "  方法三: " << len3 << endl;

    if (!consistent) {
        cout << "  [FAIL] 三种方法结果不一致！" << endl;
    }
    if (!lenCorrect) {
        cout << "  [FAIL] 期望长度 " << expectedLen << "，实际 " << len1 << endl;
    }
    if (!lcsValid) {
        cout << "  [FAIL] 方法一回溯的LCS字符串无效！" << endl;
    }
    if (allPassed) {
        cout << "  [PASS]" << endl;
        passedTests++;
    }
}

int main() {
    cout << "================================================" << endl;
    cout << "   LCS 算法测试" << endl;
    cout << "================================================" << endl;

    cout << "\n--- 边界情况：空字符串 ---" << endl;
    runTest("两个空字符串", "", "", 0);
    runTest("text1为空", "", "abc", 0);
    runTest("text2为空", "abc", "", 0);
    runTest("text1为空(较长text2)", "", "abcdefghij", 0);
    runTest("text2为空(较长text1)", "abcdefghij", "", 0);

    cout << "\n--- 边界情况：完全无交集 ---" << endl;
    runTest("完全不同的单字符", "a", "b", 0);
    runTest("完全不同的多字符", "abc", "def", 0);
    runTest("完全不同(较长)", "abcdefgh", "ijklmnop", 0);
    runTest("完全不同(长度不等)", "abcde", "fghijklmno", 0);

    cout << "\n--- 边界情况：完全相同 ---" << endl;
    runTest("两个空字符串(相同)", "", "", 0);
    runTest("单字符相同", "a", "a", 1);
    runTest("多字符完全相同", "abc", "abc", 3);
    runTest("较长字符串完全相同", "abcdefghij", "abcdefghij", 10);

    cout << "\n--- 边界情况：单字符 ---" << endl;
    runTest("单字符匹配", "x", "x", 1);
    runTest("单字符不匹配", "x", "y", 0);
    runTest("单字符包含在长串中", "a", "abc", 1);
    runTest("长串包含单字符", "abc", "a", 1);

    cout << "\n--- 标准测试用例 ---" << endl;
    runTest("README用例1: abcde vs ace", "abcde", "ace", 3);
    runTest("README用例2: abc vs abc", "abc", "abc", 3);
    runTest("README用例3: abc vs def", "abc", "def", 0);
    runTest("README用例4: bsbininm vs jmjkbkjkv", "bsbininm", "jmjkbkjkv", 1);
    runTest("README用例5: abczzdef vs abcyydef", "abczzdef", "abcyydef", 6);

    cout << "\n--- 长度差异较大(测试方法二三的swap逻辑) ---" << endl;
    runTest("text1远长于text2", "abcdefghij", "cfi", 3);
    runTest("text2远长于text1", "cfi", "abcdefghij", 3);
    runTest("text1长text2单字符(匹配)", "abcdefghij", "e", 1);
    runTest("text1长text2单字符(不匹配)", "abcdefghij", "z", 0);
    runTest("text1单字符text2长(匹配)", "e", "abcdefghij", 1);
    runTest("text1单字符text2长(不匹配)", "z", "abcdefghij", 0);

    cout << "\n--- 部分重叠 ---" << endl;
    runTest("前缀重叠", "abcdef", "abcxyz", 3);
    runTest("后缀重叠", "xyzabc", "defabc", 3);
    runTest("交错重叠", "axbycz", "abcdef", 3);
    runTest("多字符LCS(交错)", "axbyczd", "exfyzgd", 4);
    runTest("两个字符的LCS", "ab", "cabd", 2);

    cout << "\n--- 较长字符串 ---" << endl;
    runTest("较长字符串LCS", "abcdefghijklmn", "acegikm", 7);
    runTest("较长字符串(反向)", "acegikm", "abcdefghijklmn", 7);
    runTest("重复字符", "aabbbccc", "abcabcabc", 5);
    runTest("全相同字符", "aaaaa", "aaa", 3);
    runTest("交替相同字符", "ababab", "bababa", 5);

    cout << "\n================================================" << endl;
    cout << "   测试结果汇总" << endl;
    cout << "================================================" << endl;
    cout << "  总计: " << totalTests << endl;
    cout << "  通过: " << passedTests << endl;
    cout << "  失败: " << (totalTests - passedTests) << endl;

    if (passedTests == totalTests) {
        cout << "\n  *** 全部测试通过 ***" << endl;
        return 0;
    } else {
        cout << "\n  *** 存在测试失败 ***" << endl;
        return 1;
    }
}
