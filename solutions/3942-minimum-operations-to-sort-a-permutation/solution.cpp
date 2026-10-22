// 3942. Minimum Operations to Sort a Permutation
// 只有两种操作：翻转整个数组、左旋一位。两者都不改变元素在环上的相邻关系，
// 所以能排好序的排列必然是「升序环」或「降序环」的某个旋转——只需判形状 + 算相位。
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return 0;
        }
        // basePos 记的是「锚点」在环上的位置：升序环里是 0，降序环里会换成 n-1
        int basePos = 0;
        bool flag = (nums[1] == 1) ? true : false;   // 0 的后面跟 1 说明是升序环

        for (int i = 1; i < n; i++) {
            // 0 和 n-1 是环的断点，前后本来就该跳变，跳过不判
            if (nums[i] == 0) {
                basePos = i;
                flag = (nums[(i + 1) % n] == 1) ? true : false;
                continue;
            } else if (nums[i] == n - 1) {
                continue;
            }
            // 相邻差同号且均为 1，才说明这一段在环上是连续的
            if ((nums[i] - nums[i - 1]) * (nums[(i + 1) % n] - nums[i]) != 1) {
                return -1;
            }
        }

        if (flag) {
            // 直接左旋 basePos 次；或翻转 → 左旋 → 再翻转，花 n - basePos + 2
            return min(basePos, n - basePos + 2);
        } else {
            // 降序环里 n-1 紧跟在 0 后面，把锚点换成它的位置再算
            basePos = (1 + basePos) % n;
            // 先旋后翻花 basePos + 1；先翻后旋再翻花 n - basePos + 1
            return min(basePos, n - basePos) + 1;
        }
    }
};
