#ifndef LCS_FULL_DP_H
#define LCS_FULL_DP_H

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

#endif
