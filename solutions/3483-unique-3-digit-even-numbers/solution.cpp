// 3483. Unique 3-Digit Even Numbers
// 先数出每个数字的个数，再按「百位 → 十位 → 个位」枚举；占掉一个数字就把计数减一，
// 保证同一位置的数字不会重复使用。个位只枚举偶数，百位从 1 起（不能有前导零）。
class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int cnt[10] = {0};
        int ans = 0;
        for (auto i : digits) {
            cnt[i]++;
        }
        for (int i = 1; i <= 9; ++i) {
            if (!cnt[i]) {
                continue;
            }
            cnt[i]--;
            for (int j = 0; j <= 9; ++j) {
                if (!cnt[j]) {
                    continue;
                }
                cnt[j]--;
                // 前两位已定，个位还剩哪个偶数，就多出一个不同的三位数
                for (int k = 0; k <= 9; k += 2) {
                    if (cnt[k]) {
                        ans++;
                    }
                }
                cnt[j]++;
            }
            cnt[i]++;
        }
        return ans;
    }
};
