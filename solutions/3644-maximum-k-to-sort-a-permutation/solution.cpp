// 3644. Maximum K to Sort a Permutation
// 答案 = 所有错位元素的按位与：k 的每一位都必须同时出现在参与交换的两个数里，
// 而每个错位元素至少要参与一次交换，所以 k 是它们的公共位子集；这个上界可达到。
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int ans = -1;   // 全 1，相与不改变任何数；扫完仍为 -1 说明本来就有序
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                ans &= nums[i];
            }
        }
        return (ans == -1) ? 0 : ans;
    }
};
