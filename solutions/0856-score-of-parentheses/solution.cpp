// 856. Score of Parentheses
// 每个紧邻的 "()" 是叶子，它的贡献是 2^(外层深度)；一次遍历把每层的加分累加起来。
class Solution {
public:
    int scoreOfParentheses(string s) {
        int score = 0;
        int depth = 0;   // 当前身处第几层括号：进 '(' 加一，遇 ')' 减一
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                depth++;
            }
            if (s[i] == ')') {
                depth--;
                // 只有 s[i-1] 是 '(' 时才是叶子；此时 depth 已退回父层，正好是 2^depth
                if (s[i - 1] == '(') {
                    score += pow(2, depth);
                }
            }
        }
        return score;
    }
};
