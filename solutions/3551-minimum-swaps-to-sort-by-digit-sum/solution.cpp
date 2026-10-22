// 3551. Minimum Swaps to Sort by Digit Sum
// 目标排列唯一：先按数位和升序、再按数值升序。把当前位置的数和目标位置的数直接互换，
// 每次交换至少让一个数归位，总次数就是最少交换数。
class Solution {
public:
    int digitSum(int num) {
        int res = 0;
        while (num) {
            res += num % 10;
            num /= 10;
        }
        return res;
    }
    int minSwaps(vector<int>& nums) {
        vector<pair<int, int>> orderedNums;
        unordered_map<int, int> pos;
        int n = nums.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            orderedNums.push_back({nums[i], digitSum(nums[i])});
            pos[nums[i]] = i;
        }
        sort(orderedNums.begin(), orderedNums.end(), [](auto a, auto b) {
            return a.second != b.second ? a.second < b.second : a.first < b.first;
        });
        for (int i = 0; i < n; i++) {
            // 已经在目标位置上的数不用动
            if (nums[i] == orderedNums[i].first) {
                continue;
            }
            pos[nums[i]] = pos[orderedNums[i].first];
            nums[pos[orderedNums[i].first]] = nums[i];
            res++;
        }
        return res;
    }
};
