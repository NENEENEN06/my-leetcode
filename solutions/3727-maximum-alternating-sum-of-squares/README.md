# 3727. Maximum Alternating Sum of Squares

- Difficulty: Medium
- Topics: Array, Greedy, Sorting
- Language: C++
- 题目链接: https://leetcode.cn/problems/maximum-alternating-sum-of-squares/

## 题目

给一个整数数组 nums，可以任意重排。重排后的交替得分按 `score = arr[0]² - arr[1]² + arr[2]² - arr[3]² + …` 计算，求所有重排中最大的得分。

## 我的思路

- 平方只与绝对值有关，元素原本的正负号在平方后完全消失，所以排序的比较依据必须是 `abs(value)`。
- 下标的奇偶决定符号：偶数位（0、2、4…）是加号，一共 `ceil(n/2)` 个；奇数位是减号，一共 `floor(n/2)` 个。
- 于是问题从「找一个最优排列」变成「把符号名额分配下去」：绝对值最大的 `ceil(n/2)` 个数拿加号，剩下的拿减号。
- 实现上按绝对值降序排一次序，前面的加上平方、后面的减去平方即可。

## 代码

```cpp
// 3727. Maximum Alternating Sum of Squares
// 平方只看绝对值，所以按 |x| 降序排；让最大的 ceil(n/2) 个数站上加号位，其余去减号位。
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        long long res = 0;
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return abs(a) > abs(b);
        });
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (i < (n + 1) / 2) {
                // 加号位共 ceil(n/2) 个，n 为奇数时正中那个也算加号
                res += nums[i] * nums[i];
            } else {
                res -= nums[i] * nums[i];
            }
        }
        return res;
    }
};
```

## 代码分析

- 正确性：正确
- 关键实现：`abs(a) > abs(b)` 作为排序关键字降序；`i < (n+1)/2` 区分加号位与减号位
- 潜在 Bug：无。几点细节：① `nums[i] * nums[i]` 是 int 乘法，当前约束 `|nums[i]| ≤ 4*10⁴` 下平方最大 1.6e9 < 2³¹−1，不会溢出，累加结果由 `long long` 承接也安全；② 比较器在 `abs` 相等时返回 false，是合法的严格弱序；③ 这段代码会**原地修改入参**（`sort` 就地排序），LeetCode 里无所谓，但如果以后在需要保留原顺序的场景复用，得自己留一份副本
- 可以改进的地方：乘法写成 `1LL * nums[i] * nums[i]` 可对约束变化免疫；不想改动入参可以先拷贝。当前约束下都不必要

## 复杂度

- 时间复杂度：O(n log n)，排序主导，后面那趟循环是 O(n)
- 空间复杂度：O(log n)，`std::sort` 的递归栈；不计排序开销则额外空间 O(1)

## 易错点

- 不要按原值大小排序：负数平方后大小关系完全变了，比较的必须是绝对值。
- 加号位的个数是 `ceil(n/2)`，n 为奇数时最后一个元素还是加号，写成 `n/2` 就会算错。
- 结果天然非负：降序排完后前半部分逐项平方都 ≥ 后半部分对应项，不用额外夹到 0 以上。
- 溢出：累加必须用 `long long`；本例中「平方」这一步恰好还在 int 范围内，是运气好而不是设计，别当成通用结论。

## 总结

交替和类问题的通用套路：把符号看成名额——加号 `ceil(n/2)` 个、减号 `floor(n/2)` 个，排序后把绝对值大的塞进加号位。这类题不用真的枚举排列，核心只有两件事：排序依据（绝对值）+ 名额个数（上取整）。

## 复盘

- 关键突破点：把「重排后求最值」翻译成「分配符号名额」，问题从排列搜索直接降到一次排序。
- 下次看到「可以任意重排 + 交替符号 + 求最大/最小」，先数符号名额，再按绝对值排序分配。
