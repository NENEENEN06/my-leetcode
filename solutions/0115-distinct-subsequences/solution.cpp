// 0115. Distinct Subsequences
// dp[i][j]：s 前缀 s[0..i] 里能凑出 t 前缀 t[0..j] 的子序列个数。
// 转移只依赖上一行，s[i] == t[j] 时把「不用 s[i]」和「用 s[i]」两种来源相加。
class Solution {
public:
    int numDistinct(string s, string t) {
        int sLen = s.size();
        int tLen = t.size();
        vector<vector<unsigned long long>> dp(sLen, vector<unsigned long long>(tLen, 0));
        // 第一列单独算：j 顺带当累加器，数 s[0..i] 里出现过几个等于 t[0] 的字符
        for (int i = 0, j = 0; i < sLen; ++i) {
            if (s[i] == t[0]) {
                j++;
            }
            dp[i][0] = j;
        }
        for (int i = 1; i < sLen; ++i) {
            for (int j = 1; j < tLen; ++j) {
                // 至少可以选择不用 s[i]，方案数从前一行继承
                dp[i][j] = dp[i - 1][j];
                if (s[i] == t[j]) {
                    // 用 s[i] 去配 t[j]，剩下的前缀怎么配都接在这里
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }
        return dp[sLen - 1][tLen - 1];
    }
};
