// 3498. Reverse Degree of a String
// 逐位累加：位置 i（从 1 起）乘上字母的反向序号（'z' 记 1、'a' 记 26，即 'z' + 1 - s[i]）。
class Solution {
public:
    int reverseDegree(string s) {
        int ans = 0;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            ans += (i + 1) * ('z' + 1 - s[i]);
        }
        return ans;
    }
};
