// 3550. Smallest Index With Digit Sum Equal to Index
// 从左往右扫，第一个「数位和 == 下标」的位置就是答案，全都不满足则返回 -1。
// 数位和靠反复取末位、再除以十来求。
class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int digitSum = 0;
            // 这里会把 nums[i] 原地削成 0，往后不再需要它的原值
            while (nums[i]) {
                digitSum += nums[i] % 10;
                nums[i] /= 10;
            }
            if (digitSum == i) {
                return i;
            }
        }
        return -1;
    }
};
