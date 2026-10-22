// 2897. Apply Operations on Array to Maximize Sum of Squares
// 操作只是把某一位从一个元素搬到另一个元素，所以每一位的「总份额」固定、可自由分配；
// 每轮尽量把每个还剩余的位都塞进同一个数（高位集中），平方和最大。
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        int cnt[32] = {0};
        int res = 0;
        const int mod = 1e9 + 7;
        // cnt[i] 是第 i 位在所有元素中出现的次数，也就是这一位能分配的份额
        for (auto &num : nums) {
            for (int i = 0; i < 32; i++) {
                if (num & (1 << i)) {
                    cnt[i]++;
                }
            }
        }
        for (int i = 0; i < k; i++) {
            long long tmp = 0;
            for (int j = 0; j < 32; j++) {
                if (cnt[j]) {
                    cnt[j]--;
                    tmp += 1 << j;
                    tmp %= mod;
                }
            }
            res += (tmp * tmp) % mod;
            res %= mod;
        }
        return res;
    }
};
