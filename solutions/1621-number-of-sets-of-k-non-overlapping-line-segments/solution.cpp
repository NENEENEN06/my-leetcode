// 1621. Number of Sets of K Non-Overlapping Line Segments
// dp[i][j]、f[i][j] 是第 i 个点在两种状态下的方案数（是否作为线段的右端点），
// 二者按下面的递推互相转移；i 个点最多切出 i - 1 条线段，所以 j 的上界是 min(k, i - 1)。
class Solution {
public:
    int numberOfSets(int n, int k) {
        int mod = 1e9 + 7;
        int ans = 0;
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        vector<vector<int>> f(n + 1, vector<int>(k + 1, 0));

        for (int i = 1; i <= n; i++) {
            f[i][0] = 1;
            for (int j = 1; j < i && j <= k; j++) {
                dp[i][j] = f[i][j - 1] + dp[i - 1][j];
                f[i][j] = dp[i - 1][j] + f[i - 1][j];
                // 每次转移后立即取模，防止中间值溢出 int
                dp[i][j] %= mod;
                f[i][j] %= mod;
            }
        }
        ans = dp[n][k] + f[n][k];
        ans %= mod;
        return ans;
    }
};
