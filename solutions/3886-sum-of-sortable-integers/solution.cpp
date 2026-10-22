// 3886. Sum of Sortable Integers
// 只有 n 的因数 k 能当块长。把数组按 k 切块，每块必须能靠循环移位变成该段排序后的样子；
// 循环移位匹配只需试 k 个偏移量，所有块都能匹配就把 k 计入答案。
class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        vector<int> orderedNums = nums;
        sort(orderedNums.begin(), orderedNums.end());
        // 先把 n 的所有因数收集起来当候选块长
        unordered_set<int> kSet;
        for (int i = 1; i <= sqrt(n); i++) {
            if (n % i == 0) {
                kSet.insert(i);
                kSet.insert(n / i);
            }
        }
        for (int k : kSet) {
            bool ok = true;
            for (int left = 0; left < n; left += k) {
                bool matched = false;
                // 试遍所有循环偏移 off，看本块能否与排序后的本段逐位对齐
                for (int off = 0; off < k; off++) {
                    for (int pos = 0; pos < k; pos++) {
                        if (nums[left + pos] != orderedNums[left + (pos + off) % k]) {
                            break;
                        }
                        if (pos == k - 1) {
                            matched = true;
                        }
                    }
                    if (matched) {
                        break;
                    }
                }
                if (!matched) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                res += k;
            }
        }
        return res;
    }
};
