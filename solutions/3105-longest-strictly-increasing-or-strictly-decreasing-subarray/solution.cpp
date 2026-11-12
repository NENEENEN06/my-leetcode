// 3105. Longest Strictly Increasing or Strictly Decreasing Subarray
// 两趟双指针：每趟维护一段单调区间的左端点 l 与右端点 r，
// 一旦 nums[r] 破坏当前单调性，就把 l 挪到 r（新区间从 r 重新起算）。
class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        int l = 0, r = 0;
        // 第一趟：最长严格递增段，nums[r] <= nums[r-1] 就断开
        while (r < n) {
            ans = max(ans, r - l + 1);
            r++;
            if (r == n) {
                break;
            }
            if (nums[r] <= nums[r - 1]) {
                l = r;
            }
        }
        // 第二趟：最长严格递减段，nums[r] >= nums[r-1] 就断开
        l = 0;
        r = 0;
        while (r < n) {
            ans = max(ans, r - l + 1);
            r++;
            if (r == n) {
                break;
            }
            if (nums[r] >= nums[r - 1]) {
                l = r;
            }
        }
        return ans;
    }
};
