class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        int n = nums.size();
        if (n <= 3) {
            return 0;
        } else {
            sort(nums.begin(), nums.end());
            // 改两个元素只可能砍掉「一头一尾」或「同一头两个」
            return min(nums[n - 2] - nums[1], min(nums[n - 3] - nums[0], nums[n - 1] - nums[2]));
        }
    }
};
