// 2333. Minimum Sum of Squared Difference
// 全部 k1+k2 次减一都该花在差值最大的位置：排序后从上往下把元素削成一个平台。
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long res = 0;
        int n = nums1.size();
        vector<long long> diffs(n);
        for (int i = 0; i < n; i++) {
            diffs[i] = abs(nums1[i] - nums2[i]);
        }
        long long budget = k1 + k2;   // 总共可用的单点减一次数
        sort(diffs.begin(), diffs.end(), greater<long long>());
        diffs.push_back(0);   // 哨兵，保证下面访问 pos+1 不越界
        long long prefix = 0;
        int pos = 0;
        while (pos < n) {
            prefix += diffs[pos];
            // 把前 pos+1 个一起削到 diffs[pos+1] 的代价是 prefix - diffs[pos+1]*(pos+1)
            if (prefix - diffs[pos + 1] * (pos + 1) > budget) {
                budget -= prefix - diffs[pos] * (pos + 1);
                break;
            }
            pos++;
        }
        if (pos == n) {
            return 0;   // 全部能削到 0，平方和自然为 0
        }
        for (int i = 0; i < n; i++) {
            if (i <= pos) {
                // 前 pos+1 个平摊剩余次数：先降到同一高度，余数再给最前面几个各多减 1
                diffs[i] = diffs[pos] - budget / (pos + 1);
                if (i < budget % (pos + 1)) {
                    diffs[i]--;
                }
            }
            res += diffs[i] * diffs[i];
        }
        return res;
    }
};
