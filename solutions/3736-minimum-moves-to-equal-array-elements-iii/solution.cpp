// 3736. Minimum Moves to Equal Array Elements III
// 每次只能给一个元素 +1，最优目标值必然是数组最大值；一趟扫描时
// 维护 nums[0..i] 已经拉平后的公共高度（就地写回 nums[i]），
// 高度抬升 d 时左边 i 个元素要各补 d，抬不动就直接把当前元素补上去。
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int res = 0;                      // 累计操作次数
        int n = nums.size();

        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[i - 1]) {
                // 当前元素比左侧已拉平的高度低：把它补上去，代价就是差值
                res += nums[i - 1] - nums[i];
                nums[i] = nums[i - 1];
            }
            else {
                // 当前元素更高：前面的 i 个元素都要各补 (nums[i] - nums[i-1])
                res += i * (nums[i] - nums[i - 1]);
            }
        }

        return res;
    }
};
