// 1614. Maximum Nesting Depth of the Parentheses
// 只需跟踪当前括号深度 curDepth，遇到 '(' 就自增并刷新历史最大值，数字不参与判断。
class Solution {
public:
    int maxDepth(string s) {
        int curDepth = 0;
        int best = 0;
        for (auto &ch : s) {
            if (ch == '(') {
                // 先自增再比较，best 记的是曾经到达过的最大深度
                best = (++curDepth > best) ? curDepth : best;
            }
            if (ch == ')') {
                // ')' 一定与之前某个 '(' 配对，深度回退一格
                curDepth--;
            }
        }
        return best;
    }
};
