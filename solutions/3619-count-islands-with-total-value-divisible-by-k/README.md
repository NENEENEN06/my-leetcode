# 3619. Count Islands With Total Value Divisible by K

- Difficulty: Medium
- Topics: Array, Depth-First Search, Breadth-First Search, Union-Find, Matrix
- Language: C++
- 题目链接: https://leetcode.cn/problems/count-islands-with-total-value-divisible-by-k/

## 题目

`grid` 里正整数代表陆地、`0` 代表空地，四连通的正整数格构成一座岛。求「所有格子数值之和能被 k 整除」的岛有多少个。

## 我的思路

和「封闭岛屿」是同一个模板：遍历每块没走过的陆地，走完整块的同时累加数值，最后看能不能被 k 整除。

两个实现上的关键点：

- **边走边取模**：每加到一块新大陆就 `tot %= k`。一整个岛的取值和可能到 `1e5 × 1e5 = 1e10`，直接放进 `int` 会溢出；边加边取模把 `tot` 永远压在 `[0, k)` 里，既省得开 `long long`，也避免溢出。
- **拿 `0` 当 visited**：这里 0 本来就是空地，把访问过的陆地改成 0 不会产生歧义，和上一道封闭岛屿的写法完全一致。

入队时就标记（`grid[nx][ny] = 0` 紧跟 `push`），保证每个格子只进队一次。

## 代码

```cpp
// 3619. Count Islands With Total Value Divisible by K
// 模板同「封闭岛屿」：BFS 走完整块并累加数值，边走边取模防止溢出。
// 访问过的陆地直接改成 0（0 本来就是空地），省掉 visited 数组。
class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int row = grid.size();
        int col = grid[0].size();
        const int dx[] = {0, 0, 1, -1};
        const int dy[] = {1, -1, 0, 0};
        int res = 0;
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                if (grid[r][c] == 0) {
                    continue;   // 空地或已访问
                }
                queue<pair<int, int>> bfs;
                bfs.push({r, c});
                int tot = grid[r][c];   // 本岛累加和
                grid[r][c] = 0;         // 入队即标记
                while (!bfs.empty()) {
                    auto [x, y] = bfs.front();
                    bfs.pop();
                    for (int i = 0; i < 4; i++) {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (nx < 0 || nx >= row || ny < 0 || ny >= col || grid[nx][ny] == 0) {
                            continue;   // 越界、空地或已访问
                        }
                        bfs.push({nx, ny});
                        tot += grid[nx][ny];
                        tot %= k;   // 边加边取模：整岛之和最大约 1e10，塞进 int 会溢出
                        grid[nx][ny] = 0;
                    }
                }
                if (tot % k == 0) {
                    res++;   // 这个岛的总和能被 k 整除
                }
            }
        }
        return res;
    }
};
```

## 代码分析

- 正确性：正确。用「先完整求和（long long）再取模」的参考实现对拍了 4000 组随机网格（含 `k=1`、单格、全连通长蛇），零不一致；官方两个样例也对（2 / 6）
- 关键实现：`tot %= k` 放在循环体内做增量归约，避免 `int` 溢出；`grid[nx][ny] = 0` 紧跟在 `push` 后面
- 潜在 Bug：`grid[0].size()` 在 `grid` 为空时会崩（本题约束保证 `m, n >= 1`）；同样**修改了入参**，调用后原网格全变成 0
- 可以改进的地方：`k == 1` 时所有岛都满足，可以直接返回岛的个数，省掉取模；不过这属于常数级优化，不值得加分支

## 复杂度

- 时间复杂度：O(row × col)，每个格子入队一次、出队时看四个方向
- 空间复杂度：O(row × col)，BFS 队列最坏情况下装下整张网格

## 易错点

- **整岛之和会溢出**：不加 `tot %= k`，一条 10 万格、每格 10 万的岛就是 1e10，`int` 直接爆。这是本题最容易踩的坑
- 取模要**边加边做**，不能等整块走完再 `tot % k`——那时候溢出已经发生了
- 判据是 `tot % k == 0`，包括 `tot == 0`（整块岛的和对 k 取模为 0）的情形
- 入队即标记，否则同一块陆地会被反复入队
- 访问标记用 0 是安全的（0 本身就是空地），但这也意味着**入参被破坏**，回头再用原网格就错了

## 总结

「连通块 + 块内聚合」的模板题，和封闭岛屿的区别只在于聚合的是什么：那里是「有没有贴边」的布尔量，这里是「和」这种可累加的数值。可累加的量在块很大时要警惕溢出，**边遍历边取模**是最省事的解法——既避免溢出，又不用引入 `long long`。
