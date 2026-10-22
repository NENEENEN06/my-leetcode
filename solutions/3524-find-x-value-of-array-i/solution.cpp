// 3524. Find X-Value of Array I
// dp[i%2][r] 记「以 i 结尾、子数组乘积模 k 余 r」的个数，滚动两行并逐轮并入答案。
class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<long long>> dp(2, vector<long long>(k, 0));
        vector<long long> ans(k, 0);
        dp[0][nums[0] % k]++;
        ans[nums[0] % k]++;
        for (int i = 1; i < n; i++) {
            nums[i] %= k;
            for (int j = 0; j < k; j++) {
                // 以 i 结尾的乘积 = 以 i-1 结尾的某个余数再接上 nums[i]
                dp[i % 2][(j * nums[i]) % k] += dp[(i - 1) % 2][j];
                dp[(i - 1) % 2][j] = 0;   // 旧行用完即清，避免下一轮重复累加
            }
            dp[i % 2][nums[i]]++;
            // 把「以 i 结尾」这部分统计并入总答案
            for (int j = 0; j < k; j++) {
                ans[j] += dp[i % 2][j];
            }
        }
        return ans;
    }
};
