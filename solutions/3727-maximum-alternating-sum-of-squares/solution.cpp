// 3727. Maximum Alternating Sum of Squares
// 平方只看绝对值，所以按 |x| 降序排；让最大的 ceil(n/2) 个数站上加号位，其余去减号位。
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        long long res = 0;
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return abs(a) > abs(b);
        });
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (i < (n + 1) / 2) {
                // 加号位共 ceil(n/2) 个，n 为奇数时正中那个也算加号
                res += nums[i] * nums[i];
            } else {
                res -= nums[i] * nums[i];
            }
        }
        return res;
    }
};
