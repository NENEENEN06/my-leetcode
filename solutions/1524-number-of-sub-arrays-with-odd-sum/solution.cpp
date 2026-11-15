class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int oddEnding = 0;   // 以当前元素结尾、和为奇数的子数组数量
        int evenEnding = 0;  // 以当前元素结尾、和为偶数的子数组数量
        int answer = 0;
        int MOD = 1e9 + 7;
        for (int &num : arr) {
            int prevOdd = oddEnding;
            int prevEven = evenEnding;
            if (num % 2 == 0) {
                // 当前是偶数：奇偶性不变，只多出「只有它自己」这一段偶子数组
                evenEnding = prevEven + 1;
                oddEnding = prevOdd;
            } else {
                // 当前是奇数：奇偶性整体翻转，再加「只有它自己」这一段奇子数组
                evenEnding = prevOdd;
                oddEnding = prevEven + 1;
            }
            evenEnding %= MOD;
            oddEnding %= MOD;
            answer += oddEnding;
            answer %= MOD;
        }
        return answer;
    }
};
