class Solution {
public:
    string digitSum(string s, int k) {
        while (s.size() > k) {
            string next;
            int sum = 0;
            for (int i = 0; i < s.size(); i++) {
                sum += s[i] - '0';
                // 每凑满 k 个字符，就把这一段的和转成字符串拼到末尾
                if (i % k == k - 1) {
                    next = next + to_string(sum);
                    sum = 0;
                }
            }
            // 最后不满 k 个的那一段单独收尾
            if (s.size() % k != 0) {
                next = next + to_string(sum);
            }
            s = next;
        }
        return s;
    }
};
