// 3963. Create Grid With Exactly One Path
// 只留一条 L 形通道：第一列全通、最后一行全通，其余格子全封死，于是路径唯一。
class Solution {
public:
    vector<string> createGrid(int m, int n) {
        vector<string> grid(m, string(n, '#'));
        // 第一列留空：从左上角只能一路向下走
        for (int i = 0; i < m; i++) {
            grid[i][0] = '.';
        }
        // 最后一行留空：走到底后只能一路向右走；第 0 列刚填过，从 1 开始即可
        for (int i = 1; i < n; i++) {
            grid[m - 1][i] = '.';
        }
        return grid;
    }
};
