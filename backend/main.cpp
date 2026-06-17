/**
 * 最长公共子序列 (LCS) 算法实现
 * 
 * 包含三种不同空间复杂度的实现：
 * 1. O(mn) 空间 - 求LCS及其长度
 * 2. O(2*min(m,n)) 空间 - 仅求LCS长度
 * 3. O(min(m,n)) 空间 - 仅求LCS长度
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 方法一：时间复杂度O(mn)，空间复杂度O(mn)
 * 可以求出LCS及其长度
 */
class LCS_FullDP {
public:
    /**
     * 计算LCS长度并返回LCS字符串
     * @param text1 第一个字符串
     * @param text2 第二个字符串
     * @param lcsString 输出参数，存储LCS字符串
     * @return LCS的长度
     */
    static int solve(const string& text1, const string& text2, string& lcsString) {
        int m = text1.length();
        int n = text2.length();
        
        if (m == 0 || n == 0) {
            lcsString = "";
            return 0;
        }
        
        // dp[i][j] 表示 text1[0..i-1] 和 text2[0..j-1] 的LCS长度
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // 填充DP表
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // 回溯构造LCS字符串
        int lcsLen = dp[m][n];
        lcsString.resize(lcsLen);
        int i = m, j = n, idx = lcsLen - 1;
        
        while (i > 0 && j > 0) {
            if (text1[i - 1] == text2[j - 1]) {
                lcsString[idx--] = text1[i - 1];
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        
        return lcsLen;
    }
};

/**
 * 方法二：时间复杂度O(mn)，空间复杂度O(2*min(m,n))
 * 仅求LCS长度，使用两行滚动数组
 */
class LCS_TwoRows {
public:
    /**
     * 计算LCS长度
     * @param text1 第一个字符串
     * @param text2 第二个字符串
     * @return LCS的长度
     */
    static int solve(const string& text1, const string& text2) {
        int m = text1.length();
        int n = text2.length();
        
        if (m == 0 || n == 0) {
            return 0;
        }
        
        // 确保 n 是较小的维度，以优化空间
        const string& s1 = (m < n) ? text2 : text1;
        const string& s2 = (m < n) ? text1 : text2;
        int len1 = s1.length();
        int len2 = s2.length();  // len2 是较小的长度
        
        // 使用两行滚动数组
        vector<int> prev(len2 + 1, 0);
        vector<int> curr(len2 + 1, 0);
        
        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    curr[j] = prev[j - 1] + 1;
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            // 交换prev和curr
            swap(prev, curr);
        }
        
        return prev[len2];
    }
};

/**
 * 方法三：时间复杂度O(mn)，空间复杂度O(min(m,n))
 * 仅求LCS长度，使用单行数组
 */
class LCS_OneRow {
public:
    /**
     * 计算LCS长度
     * @param text1 第一个字符串
     * @param text2 第二个字符串
     * @return LCS的长度
     */
    static int solve(const string& text1, const string& text2) {
        int m = text1.length();
        int n = text2.length();
        
        if (m == 0 || n == 0) {
            return 0;
        }
        
        // 确保 n 是较小的维度，以优化空间
        const string& s1 = (m < n) ? text2 : text1;
        const string& s2 = (m < n) ? text1 : text2;
        int len1 = s1.length();
        int len2 = s2.length();  // len2 是较小的长度
        
        // 使用单行数组
        vector<int> dp(len2 + 1, 0);
        
        for (int i = 1; i <= len1; i++) {
            int prev = 0;  // 保存dp[i-1][j-1]的值
            for (int j = 1; j <= len2; j++) {
                int temp = dp[j];  // 保存当前dp[j]（即dp[i-1][j]）
                if (s1[i - 1] == s2[j - 1]) {
                    dp[j] = prev + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                prev = temp;  // 更新prev为dp[i-1][j]，供下一轮使用
            }
        }
        
        return dp[len2];
    }
};

/**
 * 打印分隔线
 */
void printSeparator(const string& title) {
    cout << "\n========================================" << endl;
    cout << title << endl;
    cout << "========================================" << endl;
}

/**
 * 验证字符串是否只包含小写字母
 */
bool isValidInput(const string& s) {
    for (char c : s) {
        if (c < 'a' || c > 'z') {
            return false;
        }
    }
    return true;
}

/**
 * 运行LCS算法并输出结果
 */
void runLCS(const string& text1, const string& text2) {
    cout << "\n输入信息：" << endl;
    cout << "text1 = \"" << text1 << "\" (长度: " << text1.length() << ")" << endl;
    cout << "text2 = \"" << text2 << "\" (长度: " << text2.length() << ")" << endl;
    
    // 方法一：O(mn) 空间，求LCS及其长度
    printSeparator("方法一：空间复杂度 O(m*n)");
    cout << "特点：可以求出LCS字符串及其长度" << endl;
    string lcsString;
    int len1 = LCS_FullDP::solve(text1, text2, lcsString);
    if (len1 == 0) {
        cout << "结果：不存在公共子序列" << endl;
        cout << "LCS长度：0" << endl;
    } else {
        cout << "LCS长度：" << len1 << endl;
        cout << "LCS序列：\"" << lcsString << "\"" << endl;
    }
    
    // 方法二：O(2*min(m,n)) 空间，仅求LCS长度
    printSeparator("方法二：空间复杂度 O(2*min(m,n))");
    cout << "特点：使用两行滚动数组，仅求LCS长度" << endl;
    int len2 = LCS_TwoRows::solve(text1, text2);
    if (len2 == 0) {
        cout << "结果：不存在公共子序列" << endl;
        cout << "LCS长度：0" << endl;
    } else {
        cout << "LCS长度：" << len2 << endl;
    }
    
    // 方法三：O(min(m,n)) 空间，仅求LCS长度
    printSeparator("方法三：空间复杂度 O(min(m,n))");
    cout << "特点：使用单行数组，仅求LCS长度" << endl;
    int len3 = LCS_OneRow::solve(text1, text2);
    if (len3 == 0) {
        cout << "结果：不存在公共子序列" << endl;
        cout << "LCS长度：0" << endl;
    } else {
        cout << "LCS长度：" << len3 << endl;
    }
    
    // 验证三种方法结果一致性
    printSeparator("结果验证");
    if (len1 == len2 && len2 == len3) {
        cout << "[OK] 三种方法计算结果一致，LCS长度均为：" << len1 << endl;
    } else {
        cout << "[WARN] 警告：三种方法计算结果不一致！" << endl;
        cout << "  方法一结果：" << len1 << endl;
        cout << "  方法二结果：" << len2 << endl;
        cout << "  方法三结果：" << len3 << endl;
    }
}

/**
 * 验证字符串是否为两个字符串的公共子序列
 */
bool isSubsequence(const string& sub, const string& text1, const string& text2) {
    int i = 0, j = 0;
    for (char c : sub) {
        while (i < (int)text1.length() && text1[i] != c) i++;
        if (i >= (int)text1.length()) return false;
        i++;
    }
    i = 0;
    for (char c : sub) {
        while (i < (int)text2.length() && text2[i] != c) i++;
        if (i >= (int)text2.length()) return false;
        i++;
    }
    return true;
}

/**
 * 运行单个测试用例
 * @return 测试通过返回 true，失败返回 false
 */
bool runTestCase(const string& testName, const string& text1, const string& text2, int expectedLen) {
    cout << "  [" << testName << "] ";
    
    string lcsString;
    int len1 = LCS_FullDP::solve(text1, text2, lcsString);
    int len2 = LCS_TwoRows::solve(text1, text2);
    int len3 = LCS_OneRow::solve(text1, text2);
    
    bool lenConsistent = (len1 == len2) && (len2 == len3);
    bool lenMatchExpected = (len1 == expectedLen);
    bool lcsValid = isSubsequence(lcsString, text1, text2) && (int)lcsString.length() == len1;
    
    if (lenConsistent && lenMatchExpected && lcsValid) {
        cout << "PASS" << endl;
        return true;
    } else {
        cout << "FAIL" << endl;
        cout << "    text1 = \"" << text1 << "\", text2 = \"" << text2 << "\"" << endl;
        cout << "    期望长度: " << expectedLen << endl;
        cout << "    FullDP长度: " << len1 << ", TwoRows长度: " << len2 << ", OneRow长度: " << len3 << endl;
        if (!lenConsistent) cout << "    错误: 三种实现结果不一致" << endl;
        if (!lenMatchExpected) cout << "    错误: 结果与期望值不符" << endl;
        if (!lcsValid) {
            cout << "    错误: LCS字符串无效" << endl;
            cout << "    LCS字符串: \"" << lcsString << "\"" << endl;
        }
        return false;
    }
}

/**
 * 运行所有测试用例
 */
void runAllTests() {
    int passed = 0;
    int total = 0;
    
    printSeparator("测试套件 - LCS 三种实现一致性验证");
    
    cout << "\n--- 边界情况：空字符串 ---" << endl;
    total += 3;
    if (runTestCase("两个都为空", "", "", 0)) passed++;
    if (runTestCase("第一个为空", "", "abcde", 0)) passed++;
    if (runTestCase("第二个为空", "abcde", "", 0)) passed++;
    
    cout << "\n--- 边界情况：完全无交集 ---" << endl;
    total += 3;
    if (runTestCase("完全不同的字符", "abc", "xyz", 0)) passed++;
    if (runTestCase("单字符无交集", "a", "b", 0)) passed++;
    if (runTestCase("长串无交集", "abcdefghij", "klmnopqrst", 0)) passed++;
    
    cout << "\n--- 边界情况：完全相同 ---" << endl;
    total += 4;
    if (runTestCase("单字符相同", "a", "a", 1)) passed++;
    if (runTestCase("短串相同", "abc", "abc", 3)) passed++;
    if (runTestCase("长串相同", "abcdefghij", "abcdefghij", 10)) passed++;
    if (runTestCase("重复字符相同", "aaaaa", "aaaaa", 5)) passed++;
    
    cout << "\n--- 边界情况：单字符 ---" << endl;
    total += 2;
    if (runTestCase("单字符匹配", "a", "a", 1)) passed++;
    if (runTestCase("单字符不匹配", "a", "b", 0)) passed++;
    
    cout << "\n--- 子序列关系 ---" << endl;
    total += 3;
    if (runTestCase("一个是另一个的子序列", "ace", "abcde", 3)) passed++;
    if (runTestCase("长串包含短串", "abcde", "ace", 3)) passed++;
    if (runTestCase("首字符公共", "abcdef", "axy", 1)) passed++;
    
    cout << "\n--- 经典测试用例 ---" << endl;
    total += 4;
    if (runTestCase("经典用例1", "abcde", "ace", 3)) passed++;
    if (runTestCase("经典用例2", "abc", "abc", 3)) passed++;
    if (runTestCase("经典用例3", "abc", "def", 0)) passed++;
    if (runTestCase("经典用例4", "bl", "yby", 1)) passed++;
    
    cout << "\n--- 不对称长度 ---" << endl;
    total += 3;
    if (runTestCase("第一个远长于第二个", "abcdefghijklmnop", "ace", 3)) passed++;
    if (runTestCase("第二个远长于第一个", "ace", "abcdefghijklmnop", 3)) passed++;
    if (runTestCase("一长一短部分匹配", "abcdefghij", "fghijklmnop", 5)) passed++;
    
    cout << "\n--- 重复字符 ---" << endl;
    total += 3;
    if (runTestCase("全部重复字符", "aaaaa", "aaabaaa", 5)) passed++;
    if (runTestCase("交替重复", "ababab", "bababa", 5)) passed++;
    if (runTestCase("部分重复", "aabbaabb", "bbaabbaa", 6)) passed++;
    
    cout << "\n--- 首尾公共 ---" << endl;
    total += 3;
    if (runTestCase("仅首字符公共", "axy", "abc", 1)) passed++;
    if (runTestCase("仅尾字符公共", "xyza", "bca", 1)) passed++;
    if (runTestCase("首尾都公共", "axyzb", "amb", 2)) passed++;
    
    printSeparator("测试结果汇总");
    cout << "通过: " << passed << " / " << total << endl;
    if (passed == total) {
        cout << "[全部通过] 所有测试用例均通过！" << endl;
    } else {
        cout << "[测试失败] 有 " << (total - passed) << " 个测试用例未通过" << endl;
    }
}

int main(int argc, char* argv[]) {
    cout << "================================================" << endl;
    cout << "   最长公共子序列 (LCS) 算法演示" << endl;
    cout << "================================================" << endl;
    
    string text1, text2;
    
    if (argc >= 2 && string(argv[1]) == "--test") {
        runAllTests();
        cout << "\n程序执行完毕。" << endl;
        return 0;
    }
    
    // 支持三种输入方式：命令行参数、控制台输入、内置测试用例
    if (argc >= 3) {
        // 方式1：命令行参数输入
        text1 = argv[1];
        text2 = argv[2];
        cout << "输入方式：命令行参数" << endl;
    } else {
        // 默认模式：控制台输入
        // 提示用户输入
        // cout << "请输入两个字符串 (text1 text2): "; // 为了评测系统可能需要静默输入，但标准控制台程序通常需要提示。提示语不影响功能。
        // 根据 prompt "由控制台输入两个字符串text1，text2"，标准做法是直接读取。
        
        if (!(cin >> text1 >> text2)) {
            return 0;
        }
    }
    
    // 单组测试（命令行参数方式）
    if (!isValidInput(text1) || !isValidInput(text2)) {
        cout << "错误：输入的字符串只能包含小写英文字符（a~z）！" << endl;
        return 1;
    }
    
    runLCS(text1, text2);
    
    cout << "\n程序执行完毕。" << endl;
    
    return 0;
}
