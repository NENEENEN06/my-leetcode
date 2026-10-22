// 3876. Construct Uniform Parity Array II
// 最小值是偶数时没有可借的奇数去调整别的元素，数组里只要还有奇数就无解；
// 其余情况（最小值是奇数，或本来就全偶）总能统一奇偶。
class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int n = nums1.size();
        int minX = 1e9;
        int cnt = 0;    // 数组里奇数的个数
        for (int i = 0; i < n; ++i) {
            if (nums1[i] % 2) {
                ++cnt;
            }
            minX = min(minX, nums1[i]);
        }
        if (minX % 2 == 0 && cnt) {
            return false;
        }
        return true;
    }
};
