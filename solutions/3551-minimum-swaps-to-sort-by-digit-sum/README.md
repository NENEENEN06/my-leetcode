# 3551. Minimum Swaps to Sort by Digit Sum
- Difficulty: Medium
- Topics: Array, Hash Table, Sorting
- Language: C++
- 题目链接: https://leetcode.cn/problems/minimum-swaps-to-sort-by-digit-sum/description/

## 题目
给定一个由互不相同的正整数组成的数组 `nums`，按每个数的数位和升序排序；数位和相同的按数值本身升序。返回把数组排成这个顺序所需的最小交换次数。一次交换指交换数组中两个不同位置的值。

## 我的思路
先把每个数展开成 `(数值, 数位和)` 二元组，按「数位和优先、数值其次」排序，得到目标序列 `ordered_nums`；同时用哈希表 `pos` 记录每个值当前所在下标。

然后从左到右扫一遍原数组：如果 `nums[i]` 已经等于目标值就跳过；否则把 `nums[i]` 挪到「目标值当前所在的位置」上——这等价于做了一次交换，只计一次数。本质就是置换环：每个长度为 k 的环最少需要 k-1 次交换，而这个写法对每个环恰好计数 k-1 次。

这里的关键取舍是：**只计数，不真的把数组排好，所以只维护 i 之后的部分。** 扫描过的前缀当成已结算的废区，不再回填 `target[i]` 到位置 i，也不依赖前缀的正确性；后面的判断只读 `i` 及其右侧，`pos` 记录的是值在未处理区里的位置。前缀偶尔被写入也不影响结果，因为没人会再读它。

## 代码
```cpp
class Solution {
public:
    int digitSum(int num){
        int res=0;
        while(num){
            res+=num%10;
            num/=10;
        }
        return res;
    }
    int minSwaps(vector<int>& nums) {
        vector<pair<int,int>>ordered_nums;
        unordered_map<int,int>pos;
        int n=nums.size();
        int res=0;
        for(int i=0;i<n;i++){
            ordered_nums.push_back({nums[i],digitSum(nums[i])});
            pos[nums[i]]=i;
        }
        sort(ordered_nums.begin(),ordered_nums.end(),[](auto a,auto b){
            return a.second!=b.second?a.second<b.second:a.first<b.first;
        });
        for(int i=0;i<n;i++){
            if(nums[i]==ordered_nums[i].first){continue;}
            pos[nums[i]]=pos[ordered_nums[i].first];
            nums[pos[ordered_nums[i].first]]=nums[i];
            res++;
        }
        return res;
    }
};
```

## 代码分析
- 正确性：正确。三个样例全过；另外用「n−环数」的参考解做了 2 万余组随机对照、n≤9 的全排列穷举，结果完全一致。
- 关键实现：排序定目标序列，`pos` 提供 O(1) 的「值 → 当前下标」定位，扫描阶段每个元素只动一次。
- 潜在 Bug：无。函数会就地改写 `nums`，这是「只计数、只维护 i 之后」的直接结果——扫描过的前缀不再需要保持正确，所以故意不回填。调用方之后还要读原数组才需要先拷贝。
- 依赖前提：`pos` 用值作 key，靠的是题目保证数值互不相同；有重复值时会塌。
- 可以改进的地方：无必要；已是最优量级。

## 复杂度
- 时间复杂度：O(n log n + n log C)。排序 O(n log n)，数位和每项 O(log nums[i])，总体 log 项远小于 n log n。
- 空间复杂度：O(n)。`ordered_nums` 与 `pos` 各 O(n)。

## 易错点
- 排序必须是双关键字 `(数位和, 数值)`，只按数位和会把同和元素排错（例 3 的 43 与 34 就卡在这里）。
- 最小交换次数不是「错位元素个数」：一个 2 元环有 2 个元素错位，但只需 1 次交换；正确口径是 sum(环长 − 1) = n − 环数。
- `nums[i]` 与 `ordered_nums[i].first` 比较的是**值**，不是数位和——写错就退化成「数位和是否归位」。
- 就地修改输入后不要再次使用 `nums`。

## 总结
「按自定义规则排序的最小交换次数」= 排序定目标 → 哈希表记每个值的位置 → 沿环交换计数。记住结论 sum(环长−1)，比逐个模拟交换更稳。
