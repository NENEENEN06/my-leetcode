// 3863. Minimum Operations to Sort a String
// 一步能把任意字符挪到任意位置，所以答案只取决于两端的情况：
// flag 记原串是否已升序，minPos / maxPos 分别是最小、最大字符所在位置。
class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        // 长度只有 2 且逆序时，单独一步换不掉顺序，无解
        if (n == 2 && s[0] > s[1]) {
            return -1;
        }
        bool flag = true;
        int minPos = 0;
        int maxPos = n - 1;
        for (int i = 1; i < n; i++) {
            if (flag && s[i] < s[i - 1]) {
                flag = false;
            }
            minPos = (s[i] < s[minPos]) ? i : minPos;
            maxPos = (s[n - 1 - i] > s[maxPos]) ? (n - 1 - i) : maxPos;
        }
        if (flag) {
            return 0;
        }
        // 最小或最大字符已经贴在正确的一端，一步就够
        if (minPos == 0 || maxPos == n - 1) {
            return 1;
        }
        // 两者恰好互换在两端，需要先挪一个再补回来，共三步
        if (minPos == n - 1 && maxPos == 0) {
            return 3;
        }
        return 2;
    }
};
