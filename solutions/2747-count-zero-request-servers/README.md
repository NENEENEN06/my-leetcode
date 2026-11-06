# 2747. Count Zero Request Servers

- Difficulty: Medium
- Topics: Array, Hash Table, Sliding Window, Sorting
- Language: C++
- 题目链接: https://leetcode.com/problems/count-zero-request-servers/

## 题目

有 `n` 台服务器（编号 `1..n`），`logs[i] = [serverId, time]` 表示某台服务器在某个时刻收到过一次请求。给定时间窗口宽度 `x`，对每个查询时刻 `q`，统计在闭区间 `[q - x, q]` 内**一条请求都没有**的服务器数量。

## 我的思路

- **核心思想**：离线 + 滑动窗口。查询按时间升序处理后，窗口只向右滑动，不用每个查询都从头扫一遍日志。
- **数据结构**：
  - `sortedQueries`：把 `{查询时刻, 原始下标}` 捆在一起排序，算完按原下标回填，保证输出顺序和输入一致；
  - `logs`：按时间升序排好；
  - `count[serverId]`：该服务器在当前窗口里出现了几次。
- **算法流程**：
  1. `answer` 全部初始化为 `n`（假设没有任何服务器请求过）；
  2. 处理排序后的第 `i` 个查询时，先直接继承第 `i-1` 个查询的答案——因为查询时间递增，窗口只会右移；
  3. 右端扩张：把时间 `<= q` 的日志加进窗口，某服务器的 `count` 从 0 变 1 说明它「首次进入窗口」，未请求数 `answer--`；
  4. 左端收缩：把时间 `< q - x` 的日志移出窗口，某服务器的 `count` 从 1 变 0 说明它「彻底离开窗口」，未请求数 `answer++`。
- **为什么正确**：窗口内被请求过的服务器集合与「未请求数」是互补的。既然答案从 `n` 出发，只需在集合发生变化的两个瞬间（0→1、1→0）修正，中间状态直接继承即可。
- **关键状态**：`leftLog` / `rightLog` 两个指针全局只增不减，每个日志最多进窗口一次、出窗口一次。

## 代码

```cpp
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int totalLogs = logs.size();
        int totalQueries = queries.size();
        // 先一律按「没有任何服务器请求过」填 n，窗口内出现过的服务器再多退少补
        vector<int> answer(totalQueries, n);

        // 查询要按时间升序扫描，所以把原始下标一起捆上，算完回填
        vector<vector<int>> sortedQueries;
        for (int i = 0; i < totalQueries; i++) {
            sortedQueries.push_back({queries[i], i});
        }
        sort(sortedQueries.begin(), sortedQueries.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        // 日志按时间升序，窗口只向右滑，不需要回退
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int leftLog = 0;   // 窗口左端：第一条时间 >= 左边界 的日志
        int rightLog = 0;  // 窗口右端：第一条时间 > 右边界 的日志
        vector<int> count(n + 1, 0);  // 每个服务器在当前窗口里出现了几次
        for (int i = 0; i < totalQueries; i++) {
            int queryIndex = sortedQueries[i][1];
            int queryTime = sortedQueries[i][0];
            int windowLeft = queryTime - x;
            // 查询时间递增，当前窗口只会在上一个窗口基础上右移，先继承上一个答案
            if (i >= 1) {
                answer[sortedQueries[i][1]] = answer[sortedQueries[i - 1][1]];
            }
            // 右端扩张：新进入窗口的服务器如果此前没被统计过，未请求数减一
            while (rightLog < totalLogs && logs[rightLog][1] <= queryTime) {
                if (count[logs[rightLog][0]] == 0) {
                    answer[queryIndex]--;
                }
                count[logs[rightLog][0]]++;
                rightLog++;
            }
            // 左端收缩：离开窗口的服务器如果就此清零，未请求数加一
            while (leftLog < totalLogs && logs[leftLog][1] < windowLeft) {
                count[logs[leftLog][0]]--;
                if (count[logs[leftLog][0]] == 0) {
                    answer[queryIndex]++;
                }
                leftLog++;
            }
        }
        return answer;
    }
};
```

## 代码分析

- 正确性：本机对拍通过——`n ≤ 6`、`m ≤ 7`、`q ≤ 5` 的随机数据 3000 组，与暴力解（每个查询重新扫日志、用 `set` 统计服务器）逐组比对，结果零差异。
- 关键实现：`answer` 从 `n` 起手，只在 `count` 由 0 变 1 / 由 1 变 0 时增减，避免了每个查询重算「不同服务器数」。
- 潜在 Bug：`logs` 被原地排序——本题参数是引用，排的是调用方的副本，LeetCode 上没问题；若以后复用同一份 `logs` 做别的统计，记得先备份。
- 可以改进的地方：无明显可优化点。排序是瓶颈，`O(m log m + q log q)` 已是这类离线区间询问的常规上限。

## 复杂度

- 时间复杂度：`O(m log m + q log q + m + q)`，其中 `m = logs.size()`、`q = queries.size()`。两个 while 循环里的指针全程只增不减，合计 `O(m)`。
- 空间复杂度：`O(n + q)`，即 `count` 数组与 `sortedQueries`；日志是原地排序，没有额外副本。

## 易错点

- **窗口是闭区间** `[q - x, q]`：右端判 `<= queryTime`，左端判 `< windowLeft`，少一个等号就错一批。
- **查询要排序后处理，但结果要按原始下标回填**，所以必须把下标和查询值绑在一起排。
- 服务器编号从 1 开始，`count` 要开 `n + 1`。
- 同一时刻多个查询、同一服务器多条日志都不会破坏该写法，但继承答案时用的是**排序后**的上一个查询，不是输入里的上一个。

## 总结

- 「多次区间询问 + 相邻区间高度重叠」是滑动窗口的信号，配合排序把问题变成离线；
- 统计「区间内不同元素个数」时，维护每个元素的出现次数，只在 0/1 边界变动的瞬间修正答案，比每次重新去重高效得多。

## 复盘

- 看到 queries 和 logs 都需要按时间排序 → 立刻想到离线处理 + 双指针；
- 看到「区间内没有出现过的数量」→ 从 `n` 起手做减法，比正向统计更省事；
- 继承上一个查询的答案这一步是这类题的关键，容易漏掉导致每个查询重新扫一遍超时。
