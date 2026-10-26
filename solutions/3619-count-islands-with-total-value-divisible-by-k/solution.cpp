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
