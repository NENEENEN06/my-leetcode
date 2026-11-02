// 462. Minimum Moves to Equal Array Elements II
// 让所有元素相等的目标值取中位数时总移动次数最小；排序后让最小与最大配对相减，
// 每一对的差恰好是两端到中位数的距离之和。
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        int res = 0;

        // 中位数是「绝对偏差之和」最小的点，排序后才能成对取差
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n / 2; i++) {
            res += nums[n - 1 - i] - nums[i];
        }

        return res;
    }
};
