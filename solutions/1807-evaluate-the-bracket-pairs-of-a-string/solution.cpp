// 1807. Evaluate the Bracket Pairs of a String
// 括号内的字符串去映射表里查，查到换成 value，查不到换成 '?'；括号外的字符原样输出。
class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> table;   // key -> value
        string res;
        for (auto& row : knowledge) {
            table[row[0]] = row[1];
        }
        int len = s.size();
        for (int i = 0; i < len; i++) {
            if (s[i] == '(') {
                // 先跳过 '('，再一路读到 ')' 之前，中间这段就是 key
                i++;
                string key;
                for (; s[i] != ')'; i++) {
                    key += s[i];
                }
                auto it = table.find(key);
                if (it != table.end()) {
                    res += it->second;
                } else {
                    res += '?';
                }
            } else {
                res += s[i];
            }
        }
        return res;
    }
};
