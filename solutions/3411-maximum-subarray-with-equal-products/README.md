# 3411. Maximum Subarray With Equal Products

- Difficulty: Easy
- Topics: Array, Math, Sliding Window, Enumeration, Number Theory
- Language: C++
- 题目链接: https://leetcode.com/problems/maximum-subarray-with-equal-products/

## 题目

给定正整数数组 `nums`，求最长连续子数组的长度，使其元素乘积等于这些元素的最大公约数与最小公倍数的乘积。数组长度为 2 至 100，元素值为 1 至 10。

## 我的思路

不直接算乘积，而是预处理 1 到 10 的质因数指数。固定左端点，逐个加入右端点；对每个质数维护它在当前区间里的指数和、最小指数与最大指数。每次扩展后检查四个质数的指数是否都满足条件，并更新最长长度。

## 代码

来源：[力扣中国 Accepted 提交 #761420814](https://leetcode.cn/submissions/detail/761420814/)（2026-11-24 18:31，UTC+8，C++）。仅调整排版与局部变量名。

```cpp
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int primes[] = {2, 3, 5, 7};
        int bestLength = 0;
        int arrayLength = nums.size();
        vector<unordered_map<int, int>> factorExponents(11);
        for (int scanIndex = 2; scanIndex <= 10; scanIndex++) {
            int remainingValue = scanIndex;
            for (int &prime : primes) {
                while (remainingValue % prime == 0) {
                    factorExponents[scanIndex][prime]++;
                    remainingValue /= prime;
                }
            }
        }
        for (int scanIndex = 0; scanIndex < arrayLength - bestLength; scanIndex++) {
            unordered_map<int, int> productExponents = factorExponents[nums[scanIndex]];
            unordered_map<int, int> gcdExponents = factorExponents[nums[scanIndex]];
            unordered_map<int, int> lcmExponents = factorExponents[nums[scanIndex]];
            for (int rightIndex = scanIndex + 1; rightIndex < arrayLength; rightIndex++) {
                bool isProductEquivalent = true;
                for (int &prime : primes) {
                    productExponents[prime] += factorExponents[nums[rightIndex]][prime];
                    gcdExponents[prime] = min(gcdExponents[prime], factorExponents[nums[rightIndex]][prime]);
                    lcmExponents[prime] = max(lcmExponents[prime], factorExponents[nums[rightIndex]][prime]);
                    if (productExponents[prime] != gcdExponents[prime] + lcmExponents[prime]) {
                        isProductEquivalent = false;
                    }
                }
                if (isProductEquivalent) {
                    bestLength = max(bestLength, rightIndex - scanIndex + 1);
                }
            }
        }
        return bestLength;
    }
};
```

## 代码分析

- **区间不变量**：固定左端点时，先用该元素的指数初始化三张表。每加入一个右端元素，对每个质数分别执行累加、取最小、取最大，所以三张表始终分别对应当前区间的乘积、GCD 和 LCM 的质因数指数。`unordered_map::operator[]` 将缺失键初始化为 0，恰好表示某个元素不含该因子（包括元素 1）。
- **判定的充要性**：乘法会相加同一质数的指数，GCD 和 LCM 则分别取最小和最大指数。值域 1 至 10 只可能出现 2、3、5、7，按算术基本定理，四个质数都满足“指数和 = 最小指数 + 最大指数”当且仅当题目等式成立。
- **枚举与边界**：任意两个正整数都满足该等式，因为两个指数的和必等于其最小值加最大值。题目保证至少有两个元素，故跳过所有长度为 1 的区间不会影响答案。若以当前左端点起步的整个后缀也不比 `bestLength` 长，则之后的左端点更不可能改进答案，可以停止外层循环；未被剪掉的左端点会检查它的所有长度至少为 2 的区间。

## 复杂度

- 时间复杂度：平均 `O(n²)`。预处理只处理固定值域；最坏会枚举二次方级别的区间，每次更新四个质数，每次哈希表操作平均 `O(1)`。
- 空间复杂度：`O(1)`。预处理表与区间状态的大小均由固定值域决定，与 `n` 无关。

## 易错点

- 不含某质数的元素也要参与指数最小值的计算，其指数是 0；忽略 0 会把 GCD 算大。
- 不能直接用固定宽度的整数累计区间乘积，约束内的乘积也可能溢出。这里仅存指数。
- 长度为 2 的区间总合法，例如 `[2, 4]`；不能把“有共同质因数”无条件当作不合法。

## 总结

把乘积、GCD、LCM 统一表示成质因数指数，就能用加法、最小值和最大值维护区间，并避免直接计算大整数乘积。

## 复盘

先从“两项指数之和等于最小值加最大值”确定答案下界，再用剩余后缀长度做剪枝。以后遇到值域很小、但区间乘积可能很大的题，可以先试着把乘积条件转换成指数条件。
