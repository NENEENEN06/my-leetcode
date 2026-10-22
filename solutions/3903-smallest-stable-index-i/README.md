# 3903. Smallest Stable Index I

- Difficulty: Easy
- Topics: Array, Prefix Sum
- Language: C++
- 题目链接: https://leetcode.cn/problems/smallest-stable-index-i/

## 题目

给定整数数组 `nums` 和整数 `k`。下标 `i` 的「不稳定值」定义为 `max(nums[0..i]) - min(nums[i..n-1])`。若某下标的稳定值小于等于 `k`，称其为稳定下标。返回最小的稳定下标，若不存在则返回 -1。

## 我的思路

- 核心思想：分别预处理前缀最大值和后缀最小值，再从左到右找第一个满足条件的下标。
- 使用的数据结构：两个数组 `prefixMax`（前缀最大值）和 `suffixMin`（后缀最小值）。
- 算法流程：
  1. `prefixMax[i] = max(prefixMax[i-1], nums[i])`，即 `nums[0..i]` 的最大值。
  2. `suffixMin[j] = min(suffixMin[j+1], nums[j])`，即 `nums[j..n-1]` 的最小值，这里用从右往左倒序填充。
  3. 从左到右遍历，第一个满足 `prefixMax[i] - suffixMin[i] <= k` 的下标就是答案；没有则返回 -1。
- 为什么这样做：不稳定值的两个部分正好是前缀最大值与后缀最小值，提前预处理后每个下标只需 O(1) 判断。
- 关键状态 / 变量：`prefixMax`、`suffixMin`。
- 为什么能够得到正确答案：从左到右扫描，返回的第一个满足条件下标天然是最小的稳定下标。

## 代码

```cpp
// 3903. Smallest Stable Index I
// 预处理前缀最大值和后缀最小值，再从左往右找第一个「区间极差不超过 k」的位置。
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefixMax(n, nums[0]);
        vector<int> suffixMin(n, nums[n - 1]);
        // 一次循环同时推进两侧：左边攒最大值，右边攒最小值
        for (int i = 1; i < n; ++i) {
            prefixMax[i] = max(prefixMax[i - 1], nums[i]);
            suffixMin[n - i - 1] = min(suffixMin[n - i], nums[n - i - 1]);
        }
        for (int i = 0; i < n; ++i) {
            if (prefixMax[i] - suffixMin[i] <= k) {
                return i;   // 第一个满足的就是最小下标
            }
        }
        return -1;
    }
};
```

## 代码分析

- 正确性：正确。
- 关键实现：`suffixMin` 采用倒序填充 `suffixMin[n-i-1] = min(suffixMin[n-i], nums[n-i-1])`，保证 `suffixMin[j]` 是 `nums[j..n-1]` 的最小值。
- 潜在 Bug：无明显错误。注意 `prefixMax` 用 `nums[0]` 初始化、`suffixMin` 用 `nums[n-1]` 初始化，方向对应正确。
- 可以改进的地方：后缀最小值可以只用一个变量在扫描时动态维护，把空间优化到 O(1)，但当前写法更直观。

## 复杂度

- 时间复杂度：O(n)，两次线性扫描。
- 空间复杂度：O(n)，`prefixMax` 与 `suffixMin` 两个辅助数组。

## 易错点

- 后缀最小值的方向容易写错，要确保 `suffixMin[i]` 覆盖 `i..n-1` 而不是 `0..i`。
- `prefixMax` 与 `suffixMin` 的初始化值不要搞反。
- 边界情况：`n == 1` 时应返回 0（不稳定值为 `nums[0] - nums[0] = 0`，而 `k >= 0`）。
- `k == 0` 是合法的，不能漏掉。
- 数值范围 `nums[i] <= 1e9`，差值仍在 `int` 范围内，不会溢出。

## 总结

这道题是典型的前缀/后缀预处理：把「区间最大值」和「区间最小值」分别用前缀数组、后缀数组提前算好，再用一次扫描定位第一个满足条件的位置。

## 复盘

- 我哪里容易想错：后缀数组的填充方向容易与前缀数组混淆。
- 关键突破点：把不稳定值拆成前缀最大和后缀最小两个可预处理的量。
- 下次看到什么特征应该想到这个算法：看到「前缀某一段的最值 + 后缀某一段的最值」这类定义，优先考虑前缀/后缀数组预处理。
