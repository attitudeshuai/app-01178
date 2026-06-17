#ifndef LCS_TWO_ROWS_H
#define LCS_TWO_ROWS_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

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

#endif
