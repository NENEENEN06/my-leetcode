// 940. Distinct Subsequences II
// dp[i] 是以 s[i] 结尾的不同子序列个数：从右往左累加 dp[j]，
// 遇到第一个相同字符就 break（更早的以同一字符结尾的子序列已经被算过），
// j 退到 0 时再补上 s[i] 单独成串这一种。
class Solution {
public:
    int distinctSubseqII(string s) {
        int mod = 1e9 + 7;
        int ans = 1;    // 1 代表空串这一种
        int sLen = s.size();
        vector<int> dp(sLen, 0);
        dp[0] = 1;
        for (int i = 1; i < sLen; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                dp[i] += dp[j];
                dp[i] %= mod;
                if (s[i] == s[j]) {
                    break;
                }
                if (j == 0) {
                    dp[i]++;
                }
            }
            ans += dp[i];
            ans %= mod;
        }
        return ans;
    }
};
