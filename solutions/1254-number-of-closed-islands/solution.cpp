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
