# 1524. Number of Sub-arrays With Odd Sum

- Difficulty: Medium
- Topics: Array, Math, Dynamic Programming, Prefix Sum
- Language: C++
- 题目链接: https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/

## 题目

给定整数数组 `arr`，统计「元素之和为奇数」的连续子数组个数，结果对 `10^9 + 7` 取模。

## 我的思路

- **核心思想**：一次遍历，维护「以当前元素结尾」的奇数和子数组、偶数和子数组各有多少个；每加入一个新元素，只根据它的奇偶性做平移和翻转。
- **关键状态**：
  - `oddEnding`：以当前元素结尾、和为奇数的子数组数量；
  - `evenEnding`：以当前元素结尾、和为偶数的子数组数量；
  - `answer`：所有已处理位置的 `oddEnding` 累加（每一段奇数和的子数组都在它结尾处被计一次）。
- **流程**：
  1. 先存下上一轮的 `prevOdd` / `prevEven`，避免原地覆盖；
  2. 若 `num` 是偶数：和旧序列拼起来奇偶性不变，老计数原样保留，只多出「只有它自己」这一段（偶数，加到 `evenEnding`）；
  3. 若 `num` 是奇数：拼起来奇偶性整体翻转（旧的奇变偶、旧的偶变奇），再加「只有它自己」这一段（奇数，加到 `oddEnding`）；
  4. 两轮计数各取模，`answer` 累加本轮的 `oddEnding` 后取模。
- **为什么正确**：任何以 `arr[i]` 结尾的子数组，要么是单元素 `[arr[i]]`，要么是「某个以 `arr[i-1]` 结尾的子数组 + `arr[i]`」。后者的奇偶性由前者的奇偶性 XOR `arr[i]` 的奇偶性决定，所以只要知道上一轮奇/偶各多少个就能直接推出本轮，不需要回看更早的状态。

## 代码

```cpp
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int oddEnding = 0;   // 以当前元素结尾、和为奇数的子数组数量
        int evenEnding = 0;  // 以当前元素结尾、和为偶数的子数组数量
        int answer = 0;
        int MOD = 1e9 + 7;
        for (int &num : arr) {
            int prevOdd = oddEnding;
            int prevEven = evenEnding;
            if (num % 2 == 0) {
                // 当前是偶数：奇偶性不变，只多出「只有它自己」这一段偶子数组
                evenEnding = prevEven + 1;
                oddEnding = prevOdd;
            } else {
                // 当前是奇数：奇偶性整体翻转，再加「只有它自己」这一段奇子数组
                evenEnding = prevOdd;
                oddEnding = prevEven + 1;
            }
            evenEnding %= MOD;
            oddEnding %= MOD;
            answer += oddEnding;
            answer %= MOD;
        }
        return answer;
    }
};
```

## 代码分析

- 正确性：力扣站内已 AC（本机未复跑，代码取自该次 Accepted 提交）。
- 关键实现：转移方程只依赖上一轮的奇/偶计数，`prevOdd` / `prevEven` 的临时保存让「翻转」不会读到被覆盖的值。
- 潜在 Bug：`answer += oddEnding` 之后才取模，单步最大增量是 `MOD` 级别，`int` 不会溢出（`2 * 10^9 < 2.147 * 10^9`）；如果哪天忘了先 `oddEnding %= MOD`，这里就会踩到溢出。
- 可以改进的地方：`MOD` 写成 `1'000'000'007` 比 `1e9 + 7` 更严谨——后者是 `double`，靠隐式转换才变成 `int`，开 `-Wconversion` 会报警。

## 复杂度

- 时间复杂度：`O(n)`，一次遍历，每步常数操作。
- 空间复杂度：`O(1)`，只用几个整型计数。

## 易错点

- **奇变偶、偶变奇是整组对调**：不能只更新 `oddEnding` 而把 `evenEnding` 留着不动。
- **别忘了「只有它自己」这一段**：每次都要给对应奇偶性 +1，漏了会少算单元素子数组。
- **取模时机**：计数增长很快（指数级），要么每步取模，要么用 `long long` 兜着。
- 答案要的是「和为奇数」的子数组，不是「元素为奇数」的个数。

## 总结

- 「子数组计数」的常见降维方式：盯住**以 i 结尾**的答案，然后写出 `i-1 → i` 的转移。
- 只要转移只依赖「上一轮的分类计数」而不是整段历史，就能压到 `O(1)` 空间。
- 奇偶性是模 2 意义下的加法，这类题本质是「前缀和奇偶性配对」的另一种写法。

## 复盘

- 看到「和为奇数/偶数」立刻想到按奇偶性分类计数，而不是去枚举子数组。
- 卡点通常在「翻转」那一步：先存旧值再写新值，是避免自我污染的最省事写法。
