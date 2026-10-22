// 3904. Smallest Stable Index II
// 预处理前缀最大值 maxVal[i] 和后缀最小值 minVal[i]，之后每个下标只需 O(1) 判断。
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> maxVal(n, nums[0]);
        vector<int> minVal(n, nums[n - 1]);
        // 同一趟里往前填前缀最大值、往后填后缀最小值
        for (int i = 1; i < n; ++i) {
            maxVal[i] = max(maxVal[i - 1], nums[i]);
            minVal[n - i - 1] = min(minVal[n - i], nums[n - i - 1]);
        }
        // 从左往右找第一个「左半最大 - 右半最小 <= k」的下标
        for (int i = 0; i < n; ++i) {
            if (maxVal[i] - minVal[i] <= k) {
                return i;
            }
        }
        return -1;
    }
};
