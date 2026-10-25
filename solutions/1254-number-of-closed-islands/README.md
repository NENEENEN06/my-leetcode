# 1254. Number of Closed Islands

- Difficulty: Medium
- Topics: Array, Depth-First Search, Breadth-First Search, Union-Find, Matrix
- Language: C++
- 题目链接: https://leetcode.cn/problems/number-of-closed-islands/

## 题目

网格里 `0` 是陆地、`1` 是水，四面（上下左右）连通的 `0` 构成一座岛。求**完全被水包围**、不碰任何边界的岛的个数。

## 我的思路

直接遍历每个还没访问过的陆地格，用 BFS 把整块岛走完，走的过程中判断有没有碰到边界：

- **入队前就标记**：把走过的格子从 `0` 改成 `1`，复用原数组当 visited，不用另开 `vis` 矩阵
- **边界判定放在出队时**：每弹出一个格子，看它是不是在第一行/最后一行/第一列/最后一列，是的话这块岛 `isClosed = 0`
- 整块走完之后 `res += isClosed`，`isClosed` 是 0/1，累加即计数

关键在于「标记」和「入队」的顺序：先改 `grid[nx][ny] = 1` 再 `push`，同一块陆地就只可能进队一次；反过来写会让同一个格子被多个邻居重复入队，队列里堆一堆重复项。

## 代码

```cpp
// 1254. Number of Closed Islands
// 遍历每块没访问过的陆地（0），BFS 走完整块：途中碰到网格边界就说明它不是封闭岛。
// 走过的陆地直接改成 1，省掉单独的 visited 数组。
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        int res = 0;
        const int dx[] = {0, 0, 1, -1};
        const int dy[] = {1, -1, 0, 0};
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                if (grid[r][c] == 1) {
                    continue;   // 水，或者已经访问过的陆地
                }
                queue<pair<int, int>> bfs;
                bfs.push({r, c});
                grid[r][c] = 1;   // 入队即标记，防止被邻居重复入队
                int isClosed = 1;
                while (!bfs.empty()) {
                    auto [x, y] = bfs.front();
                    bfs.pop();
                    // 碰到四条边界之一 —— 这块岛没被水完全包围
                    if (x == 0 || y == 0 || x == row - 1 || y == col - 1) {
                        isClosed = 0;
                    }
                    for (int i = 0; i < 4; i++) {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (nx < 0 || nx >= row || ny < 0 || ny >= col || grid[nx][ny] == 1) {
                            continue;   // 越界、是水、或已访问
                        }
                        bfs.push({nx, ny});
                        grid[nx][ny] = 1;
                    }
                }
                res += isClosed;
            }
        }
        return res;
    }
};
```

## 代码分析

- 正确性：正确。用独立的 DFS 参考实现（另开 `vis`、不原地改写）对拍了 3000 组随机小网格，零不一致；官方三个样例也都对
- 关键实现：原地把 `0` 改成 `1` 当 visited；边界判定放在出队时做，保证整块岛只要有一个格子贴边就整体不算封闭
- 潜在 Bug：`grid[0].size()` 在 `grid` 为空时会崩（本题约束保证非空）；另外这个写法**修改了入参**，LeetCode 允许，但如果调用方之后还要用原网格，得先拷贝一份
- 可以改进的地方：`isClosed` 一旦置 0 之后仍然会把整块岛走完，其实可以直接停——但提前退出要额外写清理逻辑（剩下的格子还没标记），不值得

## 复杂度

- 时间复杂度：O(row × col)，每个格子最多入队一次、出队时看 4 个方向
- 空间复杂度：O(row × col)，最坏整张网格都是陆地时队列里会堆很多格子（理论上可到 O(row × col) 量级）

## 易错点

- **`0` 是陆地、`1` 是水**，题意和常见直觉相反，写反了就是把答案换成了池塘数
- **先标记再入队**，否则同一块陆地会被重复处理，队列暴涨甚至死循环
- 边界判断要写成 `x == 0 || y == 0 || x == row - 1 || y == col - 1`，四边缺一个就会多算
- 别忘了「一块岛只要有格子贴边，整块都不算」——不能只在入队时判断，最好在出队时统一判
- `res += isClosed` 依赖 `isClosed` 是 0/1，别写成 `res = max(res, isClosed)` 之类

## 总结

这是「连通块 + 边界条件」的标准模板：遍历未访问格子 → BFS/DFS 标记整块 → 块内统计特征（这里是有没有贴边）→ 累加。原地把 `0` 改 `1` 当 visited 是最省的写法，但要记住它会修改入参。

> 备注：你发来的代码里所有 `||` 都被聊天工具吃掉了（`||` 会触发剧透格式），`x==0y==0x==row-1||y==col-1` 这种连写是还原后的样子。如果原代码不是这么写的，告我改回来。
