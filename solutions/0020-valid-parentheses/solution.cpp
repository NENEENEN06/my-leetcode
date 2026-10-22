// 20. Valid Parentheses
// 用栈做括号匹配：左括号入栈，右括号必须与栈顶配对，扫完栈必须为空。
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        // 只登记「右括号 -> 左括号」的映射，靠 find 判断当前字符是不是右括号
        map<char, char> matchOf = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        for (auto ch : s) {
            if (matchOf.find(ch) == matchOf.end()) {
                st.push(ch);
            } else {
                // 栈空说明右括号多了一个；栈顶不配说明嵌套顺序错了
                if (st.empty() || st.top() != matchOf[ch]) {
                    return false;
                } else {
                    st.pop();
                }
            }
        }
        return st.empty();
    }
};
