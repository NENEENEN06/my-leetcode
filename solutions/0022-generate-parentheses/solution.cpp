// 22. Generate Parentheses
// BFS 枚举所有前缀合法的括号串，队列元素是「当前字符串 + 尚未配对的左括号数」。
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        queue<pair<string, int>> q;
        q.push({"(", 1});   // 第一个字符只能是 '('
        while (!q.empty()) {
            auto [curStr, openCnt] = q.front();
            q.pop();
            int len = curStr.size();
            if (len == 2 * n && openCnt == 0) {
                res.push_back(curStr);   // 长度用满且括号全部配对，才是一个解
            }
            // 长度没到 2n 才能继续往后接字符
            if (len < 2 * n) {
                // 有未配对的 '(' 才能收一个 ')'
                if (openCnt <= n && openCnt > 0) {
                    q.push({curStr + ')', openCnt - 1});
                }
                // 左括号还没到 n 个才能再开一个
                if (openCnt < n && openCnt >= 0) {
                    q.push({curStr + '(', openCnt + 1});
                }
            }
        }
        return res;
    }
};
