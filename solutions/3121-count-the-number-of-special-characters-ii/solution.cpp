// 3121. Count the Number of Special Characters II
// 小写字母只看最后一次出现、大写字母只看第一次出现，先记位置再逐字母比较前后顺序。
class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_map<char, int> lastIdx;   // 小写记最后出现位置，大写记第一次出现位置
        int res = 0;
        int n = word.size();
        for (int i = 0; i < n; i++) {
            // 小写无条件覆盖成最新位置；大写只在未记录时写入，即保留第一次
            if (word[i] >= 'a' || lastIdx.find(word[i]) == lastIdx.end()) {
                lastIdx[word[i]] = i;
            }
        }
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            if (lastIdx.find(ch) == lastIdx.end() || lastIdx.find(ch - 'A' + 'a') == lastIdx.end()) {
                continue;   // 大小写没同时出现，不可能构成特殊字符
            } else if (lastIdx[ch] > lastIdx[ch - 'A' + 'a']) {
                res++;   // 小写最后出现早于大写首次出现，顺序满足
            }
        }
        return res;
    }
};
