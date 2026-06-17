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

struct TestCase {
    string text1;
    string text2;
    int expectedLen;
    string description;
};

bool runSingleTest(const TestCase& tc, int& passed, int& total) {
    total++;

    string lcsStr;
    int len1 = LCS_FullDP::solve(tc.text1, tc.text2, lcsStr);
    int len2 = LCS_TwoRows::solve(tc.text1, tc.text2);
    int len3 = LCS_OneRow::solve(tc.text1, tc.text2);

    bool consistent = (len1 == len2 && len2 == len3);
    bool matchesExpected = (len1 == tc.expectedLen);
    bool success = consistent && matchesExpected;

    cout << "  [" << (success ? "PASS" : "FAIL") << "] " << tc.description << endl;
    cout << "       text1=\"" << tc.text1 << "\", text2=\"" << tc.text2 << "\"" << endl;
    cout << "       期望长度=" << tc.expectedLen
         << ", FullDP=" << len1
         << ", TwoRows=" << len2
         << ", OneRow=" << len3 << endl;

    if (!consistent) {
        cout << "       错误：三种实现结果不一致！" << endl;
    }
    if (!matchesExpected) {
        cout << "       错误：结果与期望值不符！" << endl;
    }
    if (success && len1 > 0) {
        cout << "       LCS=\"" << lcsStr << "\"" << endl;
    }

    if (success) {
        passed++;
    }
    return success;
}

void runTests() {
    cout << "================================================" << endl;
    cout << "   LCS 算法测试套件" << endl;
    cout << "================================================" << endl;

    vector<TestCase> testCases = {
        {"", "", 0, "两个空字符串"},
        {"abc", "", 0, "text1 非空，text2 为空"},
        {"", "xyz", 0, "text1 为空，text2 非空"},

        {"abc", "def", 0, "完全无交集（无公共字符）"},
        {"xyz", "abc", 0, "完全无交集（反向）"},
        {"a", "b", 0, "单字符无交集"},

        {"abcde", "abcde", 5, "完全相同（等长）"},
        {"a", "a", 1, "完全相同（单字符）"},
        {"same", "same", 4, "完全相同（普通长度）"},

        {"abcde", "ace", 3, "普通情况 1：子序列"},
        {"abc", "abc", 3, "普通情况 2：完全相同"},
        {"abc", "def", 0, "普通情况 3：无交集"},
        {"abcde", "aec", 2, "普通情况 4：部分公共"},
        {"bsbininm", "jmjkbkjkv", 1, "普通情况 5：仅一个公共字符"},

        {"abc", "aabbcc", 3, "text2 包含重复字符"},
        {"aabbcc", "abc", 3, "text1 包含重复字符"},
        {"aaaaa", "aaaaa", 5, "全部相同字符"},
        {"ababab", "bababa", 5, "交替重复字符"},

        {"abcdxyz", "xyzabcd", 4, "前后交叉"},
        {"abcd", "bcda", 3, "循环移位"},

        {"abcdefghij", "klmnopqrst", 0, "长字符串无交集"},
        {"abcdefghij", "abcdefghij", 10, "长字符串完全相同"},
        {"abcdefghij", "acegikmoqsuwy", 5, "长字符串部分公共"},
    };

    int passed = 0;
    int total = 0;

    printSeparator("边界情况测试");
    for (size_t i = 0; i < 6; i++) {
        runSingleTest(testCases[i], passed, total);
    }

    printSeparator("完全相同测试");
    for (size_t i = 6; i < 9; i++) {
        runSingleTest(testCases[i], passed, total);
    }

    printSeparator("普通情况测试");
    for (size_t i = 9; i < 15; i++) {
        runSingleTest(testCases[i], passed, total);
    }

    printSeparator("重复字符测试");
    for (size_t i = 15; i < 18; i++) {
        runSingleTest(testCases[i], passed, total);
    }

    printSeparator("交叉与长字符串测试");
    for (size_t i = 18; i < testCases.size(); i++) {
        runSingleTest(testCases[i], passed, total);
    }

    printSeparator("测试总结");
    cout << "  总计：" << total << " 个测试用例" << endl;
    cout << "  通过：" << passed << " 个" << endl;
    cout << "  失败：" << (total - passed) << " 个" << endl;

    if (passed == total) {
        cout << "\n[SUCCESS] 所有测试用例均通过！" << endl;
    } else {
        cout << "\n[FAILURE] 有 " << (total - passed) << " 个测试用例失败！" << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc >= 2 && string(argv[1]) == "--test") {
        runTests();
        return 0;
    }

    cout << "================================================" << endl;
    cout << "   最长公共子序列 (LCS) 算法演示" << endl;
    cout << "================================================" << endl;
    
    string text1, text2;
    
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
