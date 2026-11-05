// 1385. Find the Distance Value Between Two Arrays
// 逐个检查 arr1 的每个元素，只要 arr2 里存在一个「与它距离不超过 d」的元素，这个元素就不算数。
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int res = 0;
        for (int& num1 : arr1) {
            res++;                      // 先默认这个元素计入答案
            for (int& num2 : arr2) {
                if (abs(num1 - num2) <= d) {
                    res--;              // 找到「太近」的元素，撤销计数
                    break;              // 一个就够，后续不必再查
                }
            }
        }
        return res;
    }
};
