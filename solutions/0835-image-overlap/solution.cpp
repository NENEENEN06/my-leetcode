// 835. Image Overlap
// 枚举 img2 相对 img1 的平移量 (i, j)，平移后逐格比对，取同为 1 的重叠格数最大值。
class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        int ans = 0;
        // i、j 为偏移量，负值表示 img2 整体朝左上挪动
        for (int i = 1 - n; i < n; i++) {
            for (int j = 1 - n; j < n; j++) {
                int cnt = 0;
                for (int x = 0; x + i < n && x < n; x++) {
                    // 平移后越界的那几行没有可比的对象
                    if (x + i < 0) {
                        continue;
                    }
                    for (int y = 0; y + j < n && y < n; y++) {
                        if (y + j < 0) {
                            continue;
                        }
                        // 两图该格都是 1 才算一次重叠
                        if (img1[x + i][y + j] == 1 && img2[x][y] == 1) {
                            cnt++;
                        }
                    }
                }
                ans = max(cnt, ans);
            }
        }
        return ans;
    }
};
