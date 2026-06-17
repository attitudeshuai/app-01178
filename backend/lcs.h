#ifndef LCS_H
#define LCS_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class LCS_FullDP {
public:
    static int solve(const string& text1, const string& text2, string& lcsString) {
        int m = text1.length();
        int n = text2.length();

        if (m == 0 || n == 0) {
            lcsString = "";
            return 0;
        }

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

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

class LCS_TwoRows {
public:
    static int solve(const string& text1, const string& text2) {
        int m = text1.length();
        int n = text2.length();

        if (m == 0 || n == 0) {
            return 0;
        }

        const string& s1 = (m < n) ? text2 : text1;
        const string& s2 = (m < n) ? text1 : text2;
        int len1 = s1.length();
        int len2 = s2.length();

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
            swap(prev, curr);
        }

        return prev[len2];
    }
};

class LCS_OneRow {
public:
    static int solve(const string& text1, const string& text2) {
        int m = text1.length();
        int n = text2.length();

        if (m == 0 || n == 0) {
            return 0;
        }

        const string& s1 = (m < n) ? text2 : text1;
        const string& s2 = (m < n) ? text1 : text2;
        int len1 = s1.length();
        int len2 = s2.length();

        vector<int> dp(len2 + 1, 0);

        for (int i = 1; i <= len1; i++) {
            int prev = 0;
            for (int j = 1; j <= len2; j++) {
                int temp = dp[j];
                if (s1[i - 1] == s2[j - 1]) {
                    dp[j] = prev + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                prev = temp;
            }
        }

        return dp[len2];
    }
};

#endif
