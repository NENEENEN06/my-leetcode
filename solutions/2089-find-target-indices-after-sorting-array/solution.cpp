// 2089. Find Target Indices After Sorting Array
// 原地选择排序：内层跑完后 nums[i] 就是第 i 小的元素，边排边判定，遇到比 target 大就收工。
class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        vector<int> res;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] > nums[j]) {
                    int tmp = nums[i];
                    nums[i] = nums[j];
                    nums[j] = tmp;
                }
            }
            // 此刻 nums[i] 已是第 i 小，可以直接判断
            if (nums[i] == target) {
                res.push_back(i);
            }
            if (nums[i] > target) {
                break;   // 后面只会更大，不会再有下标
            }
        }
        return res;
    }
};
