# 2913. Subarrays Distinct Element Sum of Squares I

- Difficulty: Easy
- Topics: Array, Hash Table, Binary Indexed Tree, Segment Tree
- Language: C++
- 题目链接: https://leetcode.cn/problems/subarrays-distinct-element-sum-of-squares-i/

## 题目

给一个数组 nums，对**每一个**子数组求出「不同元素个数」的平方，把所有子数组的这些平方加起来，返回总和。

## 我的思路

- 直接枚举所有子数组：外层 `i` 定起点，内层 `j` 向右扩展终点。
- 内层边扩展边用 `unordered_set` 维护「当前子数组里出现过哪些值」，所以集合大小就是不同元素个数——不用每次重新扫一遍子数组。
- 每扩展一步（插入 `nums[j]` 之后）就把 `st.size()²` 加进答案：这一步恰好对应「以 i 为起点、以 j 为终点」的那个子数组。
- 这样每个子数组只被访问一次，`O(n²)` 个区间，每个区间的统计是均摊 O(1)。

## 代码

```cpp
class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int res=0;
        int n=nums.size();
        for(int i=0;i<n;i++){
            unordered_set<int> st;
            for(int j=i;j<n;j++){
                st.insert(nums[j]);
                res+=st.size()*st.size();
            }
        }
        return res;
    }
};
```

## 代码分析

- 正确性：正确
- 关键实现：`st` 声明在外层循环里 → 每个新起点自动清空，不需要手动 `clear()`；`res += st.size()*st.size()` 放在 `insert` **之后**，所以统计的就是含 `nums[j]` 的这个子数组
- 潜在问题：`st.size()` 返回 `size_t`（无符号），`size_t * size_t` 的结果再加到 `int res` 上是一次隐式的窄化转换。本题 `n ≤ 100`，最大总和约 `5050 × 100² ≈ 5.05e7`，int 装得下，不会出错；但如果把同一段代码搬到 n 大得多的场景，就得先把乘法结果转成 `long long`，否则可能溢出错位
- 依赖预编译头：代码里用了 `unordered_set` 但没写 `#include <unordered_set>`，LeetCode 的预编译头兜住了；本地单独编译需要补上
- 可以改进的地方：把 `res` 声明成 `long long`、写成 `res += (long long)st.size() * st.size()`，对约束变化免疫，代价是零

## 复杂度

- 时间复杂度：O(n²)（两层循环枚举所有子数组；`insert` 平均 O(1)，最坏受哈希退化影响）
- 空间复杂度：O(n)，集合最多存下整个数组的不同元素

## 易错点

- 平方的是「**不同元素的个数**」，不是元素本身——别把元素值拿去平方。
- 集合必须在外层循环里重建（或显式清空），否则会带着上一个起点的元素往下算。
- 累加要在 `insert` 之后：先插入再统计，才是「以 j 结尾」的那个子数组；顺序反了会少算一位。
- 换起点时不能复用同一个集合，也不能把集合状态在内层循环里回退——区间是「起点固定、终点递增」，集合只增不减，所以内层那层不需要回退逻辑。

## 总结

「枚举起点 + 增量维护集合」是子数组统计类问题最朴素的模板：把「区间」看成两个指针，让统计量随右指针单调更新，就能把每个区间的统计压到均摊 O(1)。本题 n ≤ 100，暴力 O(n²) 就是标准解。

## 复盘

- 关键突破点：识别出「不同元素个数」这个量适合用集合增量维护，从而避免对每个子数组重新扫一遍（那样是 O(n³)）。
- 这道题是「Ⅰ」，还有加强版（Subarrays Distinct Element Sum of Squares II，`n` 到 1e5），那版必须换成贡献法：用每个值的贡献 = 以它为「新出现」的区间数，配合单调栈/树状数组做到 O(n log n)。这版先当模板题记着，思路升级留到遇到加强版时再做。
- 下次看到「所有子数组 + 某个统计量的和」，先想能不能固定一端、让另一端单调更新统计量。
