// 3871. Count Commas in Range II
// 千分位逗号按 1000 的幂逐层统计：每跨过一层，区间 [step, n] 里的每个数都多一个逗号。
class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;
        long long step = 1000;   // 当前在统计 1000、10^6、10^9 ... 这一位
        while (step <= n) {
            ans += n - step + 1;   // 所有不小于 step 的数在这一位上都带一个逗号
            step *= 1000;
        }
        return ans;
    }
};
