# 1606. Find Servers That Handled Most Number of Requests

- Difficulty: Hard
- Topics: Array, Greedy, Heap (Priority Queue), Ordered Set
- Language: C++
- 题目链接: https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/

## 题目

`k` 台服务器编号 `0..k-1`，第 `i` 个请求在 `arrival[i]` 时刻到达、需要占用 `load[i]` 时间。分配规则：优先给编号大于等于 `i % k` 的空闲服务器中最小的那台，没有就回绕取最小的空闲服务器；一台都空不出来则丢弃该请求。求处理请求数最多的所有服务器编号。

## 我的思路

- **核心思想**：两个有序结构对撞——「空闲服务器集合」用 `set` 维护，「正在忙的服务器」用小根堆按释放时刻维护。
- **数据结构**：
  - `freeServers`（`set<int>`）：当前空闲的编号，查找「≥ i % k 的最小值」正好是 `lower_bound` 的能力；
  - `busy`（`priority_queue`，小根堆）：元素是 `{释放时刻, 服务器编号}`，堆顶就是最早空闲的那台；
  - `count[k]`：每台服务器已经处理了多少请求。
- **算法流程**：
  1. 初始 `k` 台全空闲；
  2. 每个请求到来时，先把堆顶所有「释放时刻 ≤ arrival[i]」的服务器弹回 `freeServers`；
  3. `freeServers` 为空就 `continue`（丢弃请求）；
  4. 否则 `lower_bound(i % k)` 找目标服务器，走到 `end()` 就回绕到 `begin()`；
  5. 该服务器入堆（释放时刻 = `arrival[i] + load[i]`）、从空闲集删除、`count` 加一，顺手更新最大值。
  6. 最后扫一遍 `count`，等于最大值的编号就是答案。
- **为什么正确**：题目给的分配规则本身是确定的——「≥ i%k 的最小空闲编号，否则最小空闲编号」正是 `lower_bound` + 回绕。堆保证了「谁先空闲」这件事永远按时间顺序被还原，不会出现漏放或错放。

## 代码

```cpp
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> freeServers;               // 当前空闲的服务器编号
        vector<int> count(k, 0);            // 每台服务器已处理的请求数
        vector<int> result;
        // {释放时刻, 服务器编号}，小根堆按释放时刻排序
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> busy;
        int maxCount = 0;
        int totalRequests = arrival.size();
        for (int i = 0; i < k; i++) {
            freeServers.insert(i);
        }
        for (int i = 0; i < totalRequests; i++) {
            // 到达前已经跑完的服务器放回空闲池
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                freeServers.insert(busy.top().second);
                busy.pop();
            }
            // 一台都空不出来就丢弃这次请求
            if (freeServers.size() == 0) {
                continue;
            }
            // 从 i % k 开始顺时针找第一个空闲的，找不到就回绕到最小编号
            auto pos = freeServers.lower_bound(i % k);
            if (pos == freeServers.end())
                pos = freeServers.begin();
            int serverId = *pos;
            busy.push({arrival[i] + load[i], serverId});
            freeServers.erase(serverId);
            count[serverId]++;
            maxCount = max(maxCount, count[serverId]);
        }
        for (int i = 0; i < k; i++) {
            if (count[i] == maxCount) {
                result.push_back(i);
            }
        }
        return result;
    }
};
```

## 代码分析

- 正确性：力扣站内已 AC（本机没有复跑，代码取自该次 Accepted 提交）。
- 关键实现：`lower_bound(i % k)` 拿到「≥ 起点」的第一个空闲编号；返回 `end()` 时回绕 `begin()`，正好对上题目「没有就从头找最小」的语义。
- 潜在 Bug：无。注意 `arrival[i] + load[i]` 可达 2e9 量级，用 `int` 装得下（上限 1e9 + 1e9 = 2e9 < 2.147e9），但如果题目把时间放大到 1e18 就得换 `long long`。
- 可以改进的地方：`freeServers.size() == 0` 用 `empty()` 更符合习惯；另外堆里存 `pair` 的写法在要求「同一时刻按编号」时已经天然有序（先比释放时刻、再比编号），不用额外处理。

## 复杂度

- 时间复杂度：`O((n + k) log k)`。每个请求最多一次 `lower_bound`（`O(log k)`）、一次堆 pop（每个服务器每次释放恰好被 pop 一次）、一次堆 push。
- 空间复杂度：`O(k)`，空闲集合与堆的大小都不超过 `k`，`count` 也是 `k`。

## 易错点

- **回绕**：`lower_bound` 返回 `end()` 时不是丢弃请求，而是取 `begin()`。
- **先释放再分配**：`arrival[i]` 时刻就跑完的服务器（`释放时刻 <= arrival[i]`）必须在本请求分配前放回池子，漏了会让答案偏小。
- **丢弃请求**：`freeServers` 空时要 `continue`，不能强行分配。
- **答案是多台**：最大值可能被多台服务器并列，要收集全部编号而不是只取一个。

## 总结

- 「按时间顺序、资源会被释放」这类调度题，标配是**有序集合 + 按释放时间的小根堆**。
- `set::lower_bound` 天生适合「找 ≥ x 的最小值」，回绕只是一次 `end() → begin()` 的补丁。
- 把「空闲」和「忙碌」拆成两个结构，比维护一个整体状态再扫描要省一个数量级。

## 复盘

- 看到「第 i 个请求优先 i % k 开始找」→ 立刻想到 `lower_bound`；
- 看到「load[i] 后释放」→ 小根堆按释放时刻；
- 丢请求那种分支最容易漏，写的时候先把 `continue` 那条路补上。
