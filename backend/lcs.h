/**
 * 最长公共子序列 (LCS) 算法实现
 *
 * 包含三种不同空间复杂度的实现：
 * 1. O(mn) 空间 - 求LCS及其长度
 * 2. O(2*min(m,n)) 空间 - 仅求LCS长度
 * 3. O(min(m,n)) 空间 - 仅求LCS长度
 */

#ifndef LCS_H
#define LCS_H

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

#endif // LCS_H
