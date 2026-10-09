class Solution {
public:
    int minInsertions(string s) {
        int ans = 0, need = 0;          // need：当前还需要的 ')' 个数
        for (char c : s) {
            if (c == '(') {
                // need 为奇数说明最内层 '(' 只收到一个 ')'，必须补一个才能开新括号
                if (need % 2 == 1) { ++ans; --need; }
                need += 2;              // 新 '(' 需要两个 ')'
            } else {
                --need;                 // 这个 ')' 抵掉一个需求
                if (need < 0) {         // 欠成负数：没有 '(' 可配，得补一个 '('（它欠两个）
                    ++ans;
                    need += 2;
                }
            }
        }
        return ans + need;              // 收尾：还欠的 ')' 全部补上
    }
};
