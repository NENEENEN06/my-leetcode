// 3665. Twisted Mirror Path Count
// 每个格子分别试「向下」「向右」两个起始方向：撞到镜子就转向、跳过镜子继续走，
// 落到空格才算这一步的终点。行主序扫描保证支配格子的路径数先算完。
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1'000'000'007;
        const int rows = grid.size();
        const int cols = grid[0].size();

        // 方向编号：0 = 向下，1 = 向右；dir ^= 1 就是换到另一个轴
        const int dRow[2] = {1, 0};
        const int dCol[2] = {0, 1};

        // ways[r][c]：到达 (r, c) 的路径数
        vector<vector<int>> ways(rows, vector<int>(cols, 0));
        ways[0][0] = 1;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                for (int firstDir = 0; firstDir < 2; firstDir++) {
                    int dir = firstDir;
                    int row = r;
                    int col = c;
                    // 一路走，直到落在空格上（成功）或走出边界（这条路径无效）
                    while (true) {
                        row += dRow[dir];
                        col += dCol[dir];
                        if (row >= rows || col >= cols) {
                            break;
                        }
                        if (grid[row][col] == 0) {
                            break;
                        }
                        dir ^= 1;  // 落点是镜子：转向，并跳过这面镜子继续走
                    }
                    if (row >= rows || col >= cols) {
                        continue;
                    }
                    ways[row][col] = (ways[row][col] + ways[r][c]) % MOD;
                }
            }
        }
        return ways[rows - 1][cols - 1];
    }
};
