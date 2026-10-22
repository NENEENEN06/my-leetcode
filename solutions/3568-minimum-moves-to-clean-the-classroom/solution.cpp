// 3568. Minimum Moves to Clean the Classroom
// 状压 BFS：状态是 (位置, 剩余电量, 已清理垃圾集合)，每步代价为 1；
// 同一位置同一集合只保留电量最高的那次访问，电量不更优的分支直接剪掉。
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        const int dx[] = {0, 0, 1, -1};
        const int dy[] = {1, -1, 0, 0};
        int lidCount = 0, x, y;   // 垃圾总数与起点坐标
        const int m = classroom.size();
        const int n = classroom.front().size();
        struct Point {
            int x;
            int y;
            int e;
            int mask;
            int steps;
        };
        // 给每个 'L' 编号，后面用它占位图里的一位
        vector<vector<int>> lid(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'L') {
                    lid[i][j] = lidCount++;
                }
                if (classroom[i][j] == 'S') {
                    x = i;
                    y = j;
                }
            }
        }

        int fullMask = (1 << lidCount) - 1;
        // bestEnergy[x][y][mask]：该状态下的最大剩余电量，-1 表示还没访问过
        vector<vector<vector<int>>> bestEnergy(m, vector<vector<int>>(n, vector<int>(fullMask + 1, -1)));
        queue<Point> q;
        q.push({x, y, energy, 0, 0});
        while (!q.empty()) {
            auto [x, y, e, mask, steps] = q.front();
            q.pop();
            if (mask == fullMask) {
                return steps;
            }
            // 电量不比已有的记录更优，从这里继续走不可能更早清完
            if (e <= bestEnergy[x][y][mask]) {
                continue;
            } else {
                bestEnergy[x][y][mask] = e;
            }
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                    continue;
                }
                if (classroom[nx][ny] == 'X') {
                    continue;
                }
                if (e == 0) {
                    continue;   // 没电了走不动
                }
                int nextEnergy = e - 1;
                int nextMask = mask;
                if (classroom[nx][ny] == 'L') {
                    nextMask = mask | (1 << lid[nx][ny]);
                }
                if (classroom[nx][ny] == 'R') {
                    nextEnergy = energy;   // 充电点把电量回满
                }
                q.push({nx, ny, nextEnergy, nextMask, steps + 1});
            }
        }
        return -1;
    }
};
