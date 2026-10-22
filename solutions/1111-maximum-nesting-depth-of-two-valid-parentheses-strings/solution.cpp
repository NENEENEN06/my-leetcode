// 1111. Maximum Nesting Depth of Two Valid Parentheses Strings
// 相邻字符相同就分到不同组、不同则同组，两组各自承担约一半嵌套深度。
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = seq.size();
        vector<int> group(n, 0);
        // 从第二个字符开始推：只看它和前一字符是否同类，就能保证每层嵌套被两组轮流摊掉
        for (int i = 1; i < n; i++) {
            if (seq[i] == seq[i - 1]) {
                group[i] = 1 - group[i - 1];
            } else {
                group[i] = group[i - 1];
            }
        }
        return group;
    }
};
