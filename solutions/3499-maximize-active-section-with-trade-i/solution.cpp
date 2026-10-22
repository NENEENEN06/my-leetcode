// 3499. Maximize Active Section with Trade I
// 一次交易只会把夹在两段 0 之间的整段变成 1，增益等于相邻两个 0 段长度之和，
// 取最大的那一对，再加上原本就有的 1 的个数。
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int totalOne = 0;
        int n = s.size();
        // cntZero[0] 是上一段连续 0 的长度，cntZero[1] 是当前这段
        vector<int> cntZero(2, 0);
        int best = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                totalOne++;
                continue;
            }
            // 遇到一段新的 0：上一段往后顺移，当前段从 1 开始数
            cntZero[0] = cntZero[1];
            cntZero[1] = 1;
            while (i + 1 < n && s[i + 1] == '0') {
                cntZero[1]++;
                i++;
            }
            best = max(best, cntZero[0] + cntZero[1]);
        }
        // 左侧没有 0 段就没法做交易
        if (cntZero[0] == 0) {
            return totalOne;
        }
        return best + totalOne;
    }
};
