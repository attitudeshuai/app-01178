#ifndef LCS_ONE_ROW_H
#define LCS_ONE_ROW_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

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
