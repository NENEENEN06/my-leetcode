// 3723. Maximize Sum of Squares of Digits
// 从最高位开始尽量填 9，剩下的和一次填进当前位；填不满 num 位说明无解。
class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        string res(num, '0');   // 先占满 num 位，之后逐位靠字符偏移填数字
        for (int i = 0; i < num; i++) {
            if (sum > 9) {
                res[i] += 9;
                sum -= 9;
            } else {
                res[i] += sum;
                sum = 0;
                break;
            }
        }
        if (sum) {
            return "";   // 还有没分配完的和，说明 9*num 都不够，凑不出这个数
        }
        return res;
    }
};
