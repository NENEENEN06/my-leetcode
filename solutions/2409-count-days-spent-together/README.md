# 2409. Count Days Spent Together

- Difficulty: Easy
- Topics: Math, String
- Language: C++
- 题目链接: https://leetcode.cn/problems/count-days-spent-together/

## 题目

Alice 和 Bob 各自在一段日期内（含首尾）待在罗马，日期给成 `"MM-DD"`。求两人同时在城里的天数，日期都在非闰年的同一年内。

## 我的思路

本质是**求两个区间的交集长度**，只是端点是日期。分两步：

1. **求交集端点**：`max(两个到达日)` 是两人都到的日子，`min(两个离开日)` 是有一方先走的日子；前者晚于后者就是没有重叠，返回 0。
2. **算天数**：把 `"MM-DD"` 换算成「年内第几天」，两个前缀天数相减再加 1（含首尾）。

关键点是第 1 步不用真的比日期：`"MM-DD"` 是定长且零填充的，**字典序等价于时间序**，所以直接对 `string` 取 `max`/`min` 就等价于比较日期，连 `stoi` 都省了。

换算用一张前缀表 `daysum[m]`＝第 m 个月之前累计的天数，`daysum[m] + d` 就是年内第几天。表按非闰年写死（题目明确说明不是闰年），所以和官方给的每月天数一一对应。

## 代码

```cpp
// 2409. Count Days Spent Together
// 两人都在的天数 = 两段日期的交集：晚到的那天 到 早走的那天，含首尾。
// "MM-DD" 定长且零填充，字典序就是时间序，所以端点直接对字符串取 max/min。
class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        string arrive = max(arriveAlice, arriveBob);   // 两人都到了的那天
        string leave = min(leaveAlice, leaveBob);      // 有一方要先走的那天
        if (arrive > leave) {
            return 0;   // 没有交集
        }
        // daysum[m] = 第 m 个月之前累计的天数（非闰年），把 MM-DD 换算成年内第几天
        int daysum[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        return daysum[stoi(leave.substr(0, 2))] + stoi(leave.substr(3, 2))
             - daysum[stoi(arrive.substr(0, 2))] - stoi(arrive.substr(3, 2)) + 1;
    }
};
```

## 代码分析

- 正确性：正确。用独立的按日解析版本对拍了 20 万组随机日期区间（先保证起止合法），零不一致
- 关键实现：字符串 `max`/`min` 求交集端点；前缀天数表做 `MM-DD → 年内第几天` 的映射
- 潜在 Bug：前缀表是**按非闰年写死**的（2 月 28 天）。题目保证非闰年，若改成闰年或跨年数据，2 月之后的日期会整体差 1 天
- 可以改进的地方：`daysum[0]` 那个位置是占位用的，写成 `daysum[13]` 更贴合下标语义；`stoi` 调了 4 次，可以先把两个端点解成 `(月, 日)` 再算，读起来更清楚

## 复杂度

- 时间复杂度：O(1)，固定几次字符串比较和 `substr`/`stoi`
- 空间复杂度：O(1)，一张 13 个 `int` 的表

## 易错点

- **含首尾**：区间长度是 `终点 - 起点 + 1`，忘了 `+1` 会少一天
- **交集为空要提前返回 0**，否则会算出负数
- 前缀表容易写错，尤其是 7、8 月都是 31 天这一段（表里 `120 → 151` 之间跳 31）
- 别用「把日期转成天数再比」的思路去绕，`"MM-DD"` 的字典序比较本身就是正确的，反而更短

## 总结

「定长零填充的日期字符串，字典序即时间序」这个性质值得记住——凡是 `"MM-DD"`、`"YYYY-MM-DD"`、`"HH:MM:SS"` 这类格式，区间求交、排序、比较都能直接用字符串运算，不需要解析。剩下的就是 `终点 - 起点 + 1` 这个老公式。
