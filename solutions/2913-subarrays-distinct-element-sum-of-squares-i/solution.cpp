// 2913. Subarrays Distinct Element Sum of Squares I
// 直接枚举右端点并把元素塞进集合，就能 O(1) 拿到当前子数组的去重个数，累加其平方。
class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int res = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            unordered_set<int> seen;   // 子数组 nums[i..j] 的去重元素
            for (int j = i; j < n; j++) {
                seen.insert(nums[j]);
                res += seen.size() * seen.size();
            }
        }
        return res;
    }
};
