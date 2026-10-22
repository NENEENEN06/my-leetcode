// 2267. Check if There is a Valid Parentheses String Path
// BFS 只往右下走，状态是 (格子, 当前未配对的左括号数)：'(' 加一、')' 减一，中途不能为负，
// 到终点必须恰好为 0。同一格子的同一深度只需入队一次。
class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        struct Node {
            int x;
            int y;
            int bal;   // 走到该格时未配对的左括号数量
        };
        queue<Node> q;
        // 起点就是 ')' 的话第一步前缀就已经非法
        if (grid[0][0] == ')') {
            return false;
        }
        q.push({0, 0, 1});
        int m = grid.size();
        int n = grid[0].size();
        int dx[] = {0, 1};
        int dy[] = {1, 0};
        // vis[x][y][b]：该格在该深度下是否入过队，深度上限 m+n
        vector<vector<vector<bool>>> vis(m, vector<vector<bool>>(n, vector<bool>(m + n, false)));
        vis[0][0][1] = true;
        while (!q.empty()) {
            auto [x, y, bal] = q.front();
            q.pop();
            for (int i = 0; i < 2; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= m || ny >= n) {
                    continue;
                }
                int nextBal = bal + (grid[nx][ny] == '(' ? 1 : -1);
                if (nextBal < 0) {   // 右括号多于左括号，前缀非法
                    continue;
                }
                if (nx == m - 1 && ny == n - 1 && nextBal == 0) {
                    return true;
                } else if (!vis[nx][ny][nextBal]) {
                    q.push({nx, ny, nextBal});
                    vis[nx][ny][nextBal] = true;
                }
            }
        }
        return false;
    }
};
