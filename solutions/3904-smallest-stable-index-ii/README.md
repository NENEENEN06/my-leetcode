# 3904. Smallest Stable Index II
- Difficulty: Medium
- Topics: Array, Prefix/Suffix Preprocessing
- Language: C++
- 题目链接: https://leetcode.cn/problems/smallest-stable-index-ii/description/

## 题目
给定整数数组 nums 和整数 k，找到最小的下标 i，使得前缀 [0..i] 的最大值与后缀 [i..n-1] 的最小值之差不超过 k。如果不存在则返回 -1。

## 我的思路
使用前缀最大值 + 后缀最小值的预处理方法：
- 先正向遍历计算 `maxVal[i]`：表示 nums[0..i] 的最大值
- 再反向遍历计算 `minVal[i]`：表示 nums[i..n-1] 的最小值
- 最后遍历每个下标 i，检查 `maxVal[i] - minVal[i] <= k`，第一个满足条件的即为答案

这样将每个下标的判断降到 O(1)，整体时间复杂度 O(n)。

## 代码
```cpp
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int>maxVal(n,nums[0]);
        vector<int>minVal(n,nums[n-1]);
        for(int i=1;i<n;++i){
            maxVal[i]=max(maxVal[i-1],nums[i]);
            minVal[n-i-1]=min(minVal[n-i],nums[n-i-1]);
        }
        for(int i=0;i<n;++i){
            if(maxVal[i]-minVal[i]<=k){
                return i;
            }
        }
        return -1;
    }
};
```

## 代码分析
- 正确性：正确
- 关键实现：前缀最大值数组正向填充，后缀最小值数组反向填充
- 潜在 Bug：n=0 时会越界，但 LeetCode 约束通常保证 n >= 1
- 可以改进的地方：空间可优化至 O(1)，但当前实现可读性更好

## 复杂度
- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 易错点
- minVal 必须从后往前填充，方向写反会得到错误结果
- 注意是 maxVal[i] - minVal[i]，不是 maxVal[i] - minVal[i+1]
- 下标 n-i-1 的计算容易出错

## 总结
前缀/后缀预处理是处理"某位置左右两侧信息"类问题的常用技巧，可将 O(n²) 的暴力判断优化到 O(n)。
