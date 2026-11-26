# 3360. Stone Removal Game

- Difficulty: Easy
- Topics: Math, Simulation
- Language: C++
- 题目链接: https://leetcode.cn/problems/stone-removal-game/

## 题目

石堆里有 `n` 颗石子（`1 <= n <= 50`）。Alice 先手，第一回合必须恰好拿走 10 颗，此后每回合必须比上一回合少拿 1 颗。轮到谁却拿不够规定数量，谁就输。判断 Alice 是否获胜。

## 我的思路

每回合要拿多少颗是固定的，双方都没有别的走法，所以不需要搜索。直接模拟：`remainingStones` 记录剩余石子，`requiredStones` 记录下一回合要求拿走的数量，`completedMoves` 只统计已经成功完成的回合。最后看这个计数的奇偶性。

## 代码

来源：力扣 [Accepted C++ 提交 #761652205](https://leetcode.cn/submissions/detail/761652205/)（2026-11-26 13:07:16，UTC+8）。仅调整格式和局部变量名，保留题面参数 `n`。

```cpp
class Solution {
public:
    bool canAliceWin(int n) {
        int remainingStones = n;
        int completedMoves = 0;
        int requiredStones = 10;
        while (remainingStones >= requiredStones && requiredStones > 0) {
            remainingStones -= requiredStones;
            completedMoves++;
            requiredStones--;
        }
        return completedMoves % 2 == 1;
    }
};
```

## 代码分析

- **循环不变量：** 每次检查循环条件时，`remainingStones` 等于初始石子数减去所有已完成回合拿走的总数；`requiredStones` 等于 `10 - completedMoves`。初始计数为 0，两个关系都成立。每次合法取石后，扣掉本回合数量、计数加 1、下一回合需求减 1，两个关系继续成立。
- **为何奇偶性决定胜负：** 题目范围内，前 8 次合法取石共需 52 颗，而 `n <= 50`，所以至多完成 7 回合；退出必然是因为剩余石子不够下一回合取，不会走到需求为 0。已完成回合数为奇数时，最后一步由 Alice 完成，下一位 Bob 无法取石；为偶数时轮到 Alice，包含她第一步就走不了的情况。
- **边界核对：** `n = 9` 时零回合，`n = 10` 时恰好完成第一回合，`n = 19` 时恰好完成两回合。用累计取石量的阈值区间作独立判定，本地验证了 `1 <= n <= 50` 的全部输入，结果一致。

## 复杂度

- 时间复杂度：`O(1)`。起手取石数固定，且题目范围内循环体最多运行 7 次。
- 空间复杂度：`O(1)`。只保存三个局部整数。

## 易错点

- 条件必须是 `remainingStones >= requiredStones`，刚好拿完也是合法走法。
- 只统计成功完成的回合，不把尝试失败的那次算进去。
- 奇数回合表示下一位是 Bob，而不是 Alice；判断的是**谁无法走下一步**。

## 总结

走法由规则唯一确定时，直接模拟即可；交替行动不必额外保存当前玩家，成功回合数的奇偶性已经包含这个信息。

## 复盘

遇到递减的固定消耗，先写出前几步的累计阈值（10、19、27……），就能独立检查模拟的边界。重点测恰好达到阈值和比阈值少 1 的输入，两者会让胜负翻转。
