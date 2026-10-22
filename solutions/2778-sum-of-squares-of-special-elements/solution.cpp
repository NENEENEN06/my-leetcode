// 2778. Sum of Squares of Special Elements
// 题目下标从 1 开始，所以「下标 i 能整除 n」对应代码里的 (i+1)，命中就把平方累加上去。
class Solution {
public:
    int sumOfSquares(vector<int>& nums) {
        int res = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (n % (i + 1) == 0) {
                res += nums[i] * nums[i];
            }
        }
        return res;
    }
};
