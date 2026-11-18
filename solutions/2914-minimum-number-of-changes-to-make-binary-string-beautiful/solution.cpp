class Solution {
public:
    int minChanges(string s) {
        int result = 0;
        // 每两个字符一组，组内不一致就要改一次
        for (int i = 1; i < s.size(); i += 2) {
            if (s[i] != s[i - 1]) {
                result++;
            }
        }
        return result;
    }
};
