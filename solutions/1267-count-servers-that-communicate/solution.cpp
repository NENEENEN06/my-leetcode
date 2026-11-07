// 1267. Count Servers that Communicate
// 先数出每行、每列各有多少台服务器，再逐台判「同行或同列还有第二台」，即 row[i] > 1 或 col[j] > 1。
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int res = 0;
        int m = grid.size();
        int n = grid[0].size();
        set<pair<int, int>> servers;   // 所有服务器的坐标 (i, j)，后面逐个判定
        vector<int> row(m, 0);         // row[i]：第 i 行的服务器数量
        vector<int> col(n, 0);         // col[j]：第 j 列的服务器数量
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    row[i]++;
                    col[j]++;
                    servers.insert({i, j});
                }
            }
        }
        // 同行或同列只要还有第二台服务器，这台就能通信
        for (auto [i, j] : servers) {
            if (row[i] > 1 || col[j] > 1) {
                res++;
            }
        }
        return res;
    }
};
