// 1190. Reverse Substrings Between Each Pair of Parentheses
// 栈里存左括号下标；遇到 ')' 就把栈顶下标到当前下标（连同这对括号）整段翻转。
// 由内向外逐层翻，外层翻转会把内层已翻好的内容再带回正序，最后统一删括号。
class Solution {
public:
    string reverseParentheses(string s) {
        stack<int> st;
        string res;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                st.push(i);
            }
            if (s[i] == ')') {
                // 栈顶下标与当前 i 恰好是一对括号，右端取 r+1 才是闭区间
                int leftIdx = st.top();
                int rightIdx = i;
                st.pop();
                reverse(s.begin() + leftIdx, s.begin() + rightIdx + 1);
            }
        }
        // 括号这时已被翻得七零八落，第二趟只把字母挑出来拼答案
        for (int i = 0; i < n; i++) {
            if (s[i] != '(' && s[i] != ')') {
                res += s[i];
            }
        }
        return res;
    }
};
