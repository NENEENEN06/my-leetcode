// 1477. Find Two Non-overlapping Sub-arrays Each With Target Sum
// 滑动窗口找出所有和为 target 的区间；dp[i] 记前 i 个元素中最短合法区间的长度，
// 每遇到新合法区间就用「它 + 它左侧最短的那个」更新答案。
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int left = 0, right = 0;
        int n = arr.size();
        int windowSum = 0;
        // dp[i]：arr[0..i-1] 中和为 target 的最短区间长度，100001 表示不存在
        vector<int> dp(n + 1, 100001);
        int ans = 100001;
        while (right < n) {
            windowSum += arr[right];
            // 超出 target 就从左边缩，缩到刚好不超过为止
            while (windowSum > target) {
                windowSum -= arr[left];
                left++;
            }
            dp[right + 1] = dp[right];
            if (windowSum == target) {
                // 先用还没包含自身的 dp 更新答案，才能保证两个区间不重叠
                ans = min(ans, dp[left] + right - left + 1);
                // 再用当前区间长度更新前缀最短值
                dp[right + 1] = min(dp[right], right - left + 1);
            }
            right++;
        }
        return (ans == 100001) ? -1 : ans;
    }
};
