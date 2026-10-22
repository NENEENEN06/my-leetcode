// 3903. Smallest Stable Index I
// 预处理前缀最大值和后缀最小值，再从左往右找第一个「区间极差不超过 k」的位置。
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefixMax(n, nums[0]);
        vector<int> suffixMin(n, nums[n - 1]);
        // 一次循环同时推进两侧：左边攒最大值，右边攒最小值
        for (int i = 1; i < n; ++i) {
            prefixMax[i] = max(prefixMax[i - 1], nums[i]);
            suffixMin[n - i - 1] = min(suffixMin[n - i], nums[n - i - 1]);
        }
        for (int i = 0; i < n; ++i) {
            if (prefixMax[i] - suffixMin[i] <= k) {
                return i;   // 第一个满足的就是最小下标
            }
        }
        return -1;
    }
};
