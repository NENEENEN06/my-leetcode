// 1021. Remove Outermost Parentheses
// 按嵌套深度剥离：深度从 0 加到 1 的那个 '('、以及配平回 0 的那个 ')' 属于最外层，丢掉。
class Solution {
public:
    string removeOuterParentheses(string s) {
        string res;
        int depth = 0;   // 当前嵌套深度
        for (auto ch : s) {
            if (ch == '(') {
                depth++;
                if (depth != 1) {   // 深度回到 1 的 '(' 是某个本原串的最外层
                    res += ch;
                }
            } else {
                depth--;
                if (depth != 0) {   // 把深度减到 0 的 ')' 同样是外层
                    res += ch;
                }
            }
        }
        return res;
    }
};
