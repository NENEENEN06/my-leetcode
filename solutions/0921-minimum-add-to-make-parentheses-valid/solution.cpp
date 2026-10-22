// 0921. Minimum Add to Make Parentheses Valid
// 一趟扫描记两种缺口：leftOpen 是还没配对的 '(' 数，rightClose 是配不上对的 ')' 数。
// 遇到 ')' 优先抵消一个 '('，抵不掉就说明这里缺一个左括号。
class Solution {
public:
    int minAddToMakeValid(string s) {
        int leftOpen = 0, rightClose = 0;
        for (auto &ch : s) {
            if (ch == '(') {
                leftOpen++;
            } else if (leftOpen > 0) {
                leftOpen--;
            } else {
                // 左边已没有可配的 '('，只能再补一个
                rightClose++;
            }
        }
        // 两类缺口互不重叠，相加就是最少要补的字符数
        return leftOpen + rightClose;
    }
};
