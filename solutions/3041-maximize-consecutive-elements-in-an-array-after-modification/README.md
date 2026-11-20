# 3041. Maximize Consecutive Elements in an Array After Modification

- Difficulty: Hard
- Topics: Array, Dynamic Programming, Sorting
- Language: C++
- 题目链接: https://leetcode.cn/problems/maximize-consecutive-elements-in-an-array-after-modification/

## 题目

给定一个正整数数组。每个元素可以保持原值，也可以加 `1` 一次。选出尽可能多的元素，使它们重新排列后构成一段没有重复、没有断点的连续整数，求最多能选多少个。

## 我的思路

先排序，再用哈希表做动态规划。`mp[v]` 表示只用已经处理过的元素，能拼出的、以 `v` 结尾的最长连续段长度；不存在的状态视为 `0`。

遇到 `x` 时有两种选法：把它加一，用 `mp[x] + 1` 更新 `mp[x + 1]`；或保留原值，用 `mp[x - 1] + 1` 更新 `mp[x]`。每次都与旧值取最大，这样也保留了不选当前元素的方案。

## 代码

```cpp
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 1;
        unordered_map<int, int> mp;
        for (int& x : nums) {
            mp[x + 1] = max(mp[x + 1], mp[x] + 1);
            mp[x] = max(mp[x], mp[x - 1] + 1);
            ans = max(ans, max(mp[x], mp[x + 1]));
        }
        return ans;
    }
};
```

## 代码分析

- **为什么可以先排序**：若原值 `a < b`，则 `a + 1 <= b`，修改后两者不会逆序；相同原值的元素可以交换身份，把不加一的排在加一的前面。因此，总有一种最优方案能按原值排序后的顺序拼出连续段。
- **为什么转移完整**：在已有状态上，当前元素只有不选、保留原值、加一三种选择。后两种选择分别从目标值的前一个整数接上；如果前驱不存在，`0 + 1` 就是从当前元素新开一段。只有 `mp[x]` 和 `mp[x + 1]` 可能变长，所以每轮只需用这两个状态更新 `ans`。
- 代码取自力扣 Accepted 提交，仅调整排版。

## 复杂度

- 时间复杂度：平均 `O(n log n)`。排序需要 `O(n log n)`，扫描中的哈希表操作平均每次 `O(1)`。
- 空间复杂度：`O(n)`。哈希表每轮最多涉及 `x - 1`、`x`、`x + 1` 三个键，另有排序的栈开销。

## 易错点

- 必须先更新 `mp[x + 1]`，再更新 `mp[x]`。反过来会读到本轮刚写入的状态，把同一个元素算两次；输入只有 `[1]` 就会错误地得到长度 `2`。
- 不要先去重。比如 `[1, 1, 3]` 可以让一个 `1` 保持不变、另一个变成 `2`，拼出 `[1, 2, 3]`。

## 总结

每个数只允许加一，排序后就能按连续段的顺序考虑元素。状态只需记住「结尾值」和「最长长度」，不用保存整段。

## 复盘

遇到原地更新的动态规划，先问每条转移读的是上一轮状态，还是本轮已经写过的状态。本题用 `[1]` 就能检查更新顺序，用 `[1, 1, 3]` 则能检查有没有错误地去重。
