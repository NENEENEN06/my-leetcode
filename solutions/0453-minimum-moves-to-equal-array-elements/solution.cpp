// 453. Minimum Moves to Equal Array Elements
// 每次给 n-1 个元素 +1，等价于每次只挑一个元素 -1；把所有元素削到最小值即可，
// 答案 = 总和 - n * 最小值。
class Solution {
public:
    int minMoves(vector<int>& nums) {
        // 注意：n ≤ 1e5、|nums[i]| ≤ 1e9，总和最大 1e14，int 装不下，这里必须用 long long
        long long sum = nums[0];
        int minNum = nums[0];
        int n = nums.size();

        for (int i = 1; i < n; i++) {
            sum += nums[i];
            minNum = min(minNum, nums[i]);
        }

        return static_cast<int>(sum - static_cast<long long>(minNum) * n);
    }
};
