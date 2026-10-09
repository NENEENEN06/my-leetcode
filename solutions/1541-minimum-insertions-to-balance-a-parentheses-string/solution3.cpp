class Solution {
public:
    int minInsertions(string s) {
        vector<int> need;      // 栈里存每个未闭合 '(' 还欠的 ')' 个数（初始 2）
        int ans = 0;
        for (char c : s) {
            if (c == '(') {
                if (!need.empty() && need.back() == 1) {  // 上一个 '(' 只欠 1 个，必须先补上
                    ++ans;
                    need.pop_back();
                }
                need.push_back(2);
            } else {
                if (need.empty()) {                       // 没有 '(' 可配：补一个 '('
                    ++ans;
                    need.push_back(1);                    // 本字符充当它的第一个 ')'
                } else {
                    --need.back();
                    if (need.back() == 0) need.pop_back(); // 这一对 '(' 收齐了两个 ')'
                }
            }
        }
        for (int v : need) ans += v;   // 剩下的每个 '(' 还欠 1 或 2 个 ')'
        return ans;
    }
};
