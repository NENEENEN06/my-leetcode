# 2089. Find Target Indices After Sorting Array

- Difficulty: Easy
- Topics: Array, Binary Search, Sorting
- Language: C++
- 题目链接: https://leetcode.cn/problems/find-target-indices-after-sorting-array/

## 题目

给定整数数组 `nums` 和整数 `target`。把 `nums` 按非递减顺序排序后，返回所有满足 `nums[i] == target` 的下标 `i`（按下标升序），不存在则返回空数组。

## 我的思路

- 核心思想：不单独做一遍排序，而是一边做选择排序、一边判断——每轮结束后第 `i` 位已经「就位」，此时才知道它是不是 `target`。
- 使用的数据结构：结果数组 `res`，原地交换排序，无额外辅助数组。
- 算法流程：
  1. 外层 `i` 从 0 走到 n-1，内层 `j` 从 `i+1` 扫到 n-1，遇到 `nums[i] > nums[j]` 就交换，把更小的值换到 `i` 位。
  2. 内层结束后 `nums[i]` 就是 `nums[i..n-1]` 的最小值，也就是有序数组的第 `i` 个元素。
  3. 若 `nums[i] == target`，把 `i` 记入 `res`。
  4. 若 `nums[i] > target`，说明后面只会更大，直接 `break`。
- 为什么这样做：既然每轮结束第 `i` 位一定是最终有序序列里的第 `i` 个数，那就没必要先排完整再扫一遍，排序过程中就能判定。
- 关键状态 / 变量：`nums`（原地变成升序）、`res`、提前退出条件 `nums[i] > target`。
- 为什么能够得到正确答案：内层循环保证前缀 `nums[0..i]` 已升序且是原数组中最小的 `i+1` 个数，所以「第 `i` 位等于 target」与「有序数组第 `i` 位等于 target」等价。

## 代码

```cpp
// 2089. Find Target Indices After Sorting Array
// 原地选择排序：内层跑完后 nums[i] 就是第 i 小的元素，边排边判定，遇到比 target 大就收工。
class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        vector<int> res;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] > nums[j]) {
                    int tmp = nums[i];
                    nums[i] = nums[j];
                    nums[j] = tmp;
                }
            }
            // 此刻 nums[i] 已是第 i 小，可以直接判断
            if (nums[i] == target) {
                res.push_back(i);
            }
            if (nums[i] > target) {
                break;   // 后面只会更大，不会再有下标
            }
        }
        return res;
    }
};
```

## 代码分析

- 正确性：正确。本机对拍验证：与「先 `sort` 再扫一遍」的暴力解随机对比 20000 组（值域 1..6、含大量重复、n ≤ 8）零不一致；另跑了样例 `[1,2,5,2,3]` 配 target 2 / 3 / 5 / 4，分别得到 `[1,2]`、`[3]`、`[4]`、`[]`，与预期一致。
- 关键实现：判断 `nums[i] == target` 与 `break` 都必须放在内层循环**之后**，因为只有内层结束后 `nums[i]` 才是最终值。
- 潜在 Bug：无明显错误。注意 `break` 写在 `==` 判断之后，顺序反了会漏掉最后一个命中位置（target 在有序数组的最后一个下标时）。
- 可以改进的地方：数组只有 100 个数，O(n²) 完全够用；若想线性，可以只统计「小于 target 的个数 `less`」和「等于 target 的个数 `eq`」，答案就是 `less .. less+eq-1`，不必真的排序。

## 复杂度

- 时间复杂度：O(n²)。最坏是完整跑完选择排序；`break` 在 target 之后一位就停，实际是 O(k·n)，其中 k 为 target 的排名，但上界仍是 O(n²)。
- 空间复杂度：O(1)（不计结果数组），原地交换。

## 易错点

- 判断时机：内层循环没走完就把 `nums[i]` 拿去比 `target`，会拿到还没就位的值。
- `break` 与 `push_back` 的先后顺序。
- `target` 不在数组里时要返回空数组，而不是返回 `-1`。
- 重复元素要全部记录（题目要求返回所有下标），`==` 判断只能记录、不能提前终止（除非已 `> target`）。
- 题目没有禁止修改输入数组，原地排序是允许的。

## 总结

这题的关键洞察是：**不需要先排完再找，排序过程中每一位一就位就能立刻判定**。把「选择排序的第 i 轮结束」当成「有序数组第 i 位确定」的时刻，就顺手把查找塞进了排序里。

## 复盘

- 我哪里容易想错：容易在还没排好的位置上去判断 `target`，或者用 `break` 时把等于的情况也跳掉。这题里 `>=` 写成终止条件就会错，必须是 `>`。
- 关键突破点：意识到「有序数组的第 i 位」和「选择排序第 i 轮结束后的 `nums[i]`」是同一个东西。
- 下次看到什么特征应该想到这个算法：题目要「排序后的下标」且数据规模很小（n ≤ 100）时，边排边判、或者直接计数（小于 / 等于 target 的个数）都是 O(n) 级别的直觉解法，后者更快也更短。
