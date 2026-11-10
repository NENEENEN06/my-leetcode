// 3693. Climbing Stairs II
// dp[i] = 走到第 i 级台阶的最小总成本；每步只能跨 1/2/3 级，
// 跨 d 级要多付 d^2 的平方代价，所以 dp[i] 只需要看前面三级。
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        // n = 1 / n = 2 时不构成完整的三级前驱，单独返回，也省掉下标越界
        if (n == 1) {
            return costs[0] + 1;
        }
        if (n == 2) {
            return min(costs[1] + 4, costs[0] + costs[1] + 2);
        }
        vector<int> dp(n + 1, 0);  // dp[0] = 0：起点本身不花钱
        dp[1] = costs[0] + 1;      // 0 -> 1：落地成本 + 1^2
        dp[2] = costs[1] + min(dp[1] + 1, dp[0] + 4);  // 直跳 0 -> 2，或经 1 中转
        for (int i = 3; i <= n; i++) {
            // 三种来路各试一次：+1 是一级跳的平方代价，+4 两级，+9 三级
            dp[i] = costs[i - 1] + min(dp[i - 1] + 1, min(dp[i - 2] + 4, dp[i - 3] + 9));
        }
        return dp[n];
    }
};
