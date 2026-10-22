// 3870. Count Commas in Range
// 千分位逗号只出现在 ≥1000 的数上，而 [1, n] 里这样的数每个贡献一次，共 n - 999 个。
class Solution {
public:
    int countCommas(int n) {
        return (n > 999) ? (n - 999) : 0;
    }
};
