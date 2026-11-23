# 1. Two Sum
- Difficulty: Easy
- Topics: Array, Hash Table
- Language: C++
- 题目链接: https://leetcode.cn/problems/two-sum/

## 题目
给定整数数组 `nums` 和目标值 `target`，返回两个不同的下标，使对应元素之和等于 `target`。题目保证恰有一个有效答案，返回顺序不限。

## 我的思路
从左到右扫一遍，用哈希表 `indexByValue` 记录已经扫过的值及其下标。对当前下标 `currentIndex`，先查 `target - nums[currentIndex]`。查到就把历史下标和当前下标放进 `answerIndices`，结束循环；没查到才登记当前元素。

## 代码
代码取自 LeetCode Accepted 提交 [761256098](https://leetcode.cn/problems/two-sum/submissions/761256098/)，仅调整排版和局部变量名，保留原签名和逻辑。

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indexByValue;
        vector<int> answerIndices;
        int numCount = nums.size();
        for (int currentIndex = 0; currentIndex < numCount; currentIndex++) {
            auto complementEntry = indexByValue.find(target - nums[currentIndex]);
            if (complementEntry == indexByValue.end()) {
                indexByValue[nums[currentIndex]] = currentIndex;
            } else {
                answerIndices.push_back(complementEntry->second);
                answerIndices.push_back(currentIndex);
                break;
            }
        }
        return answerIndices;
    }
};
```

## 代码分析
- **循环不变量：** 如果尚未找到答案，处理下标 `currentIndex` 前，`indexByValue` 恰好覆盖前缀中出现过的所有值；每个值映射到它最近一次出现的下标。开始时表为空；查询未命中时登记当前值，即可让不变量延续到下一轮。
- **为什么不漏解：** 设一对合法下标为 `left < right`。如果没有提前返回合法答案，扫描到 `right` 时，`nums[left]` 已在表中，且它正是 `target - nums[right]`。即使同值的较新下标覆盖了 `left`，替代下标仍小于 `right`，且值相同，因此仍然能找到合法配对。
- **重复元素与自身配对：** `[3, 3]`、目标 `6` 时，第一个 `3` 查询未命中后入表，第二个 `3` 命中下标 `0`。先查后存确保表中不可能有当前下标，所以单个 `3` 不会与自己配对。
- **负数与无解：** 负数照常作为哈希键，例如 `[-3, 4, 7]`、目标 `1` 时，处理 `4` 会命中 `-3`。如果把实现用于题面之外的无解输入，循环没有命中，`answerIndices` 保持为空；官方用例保证有解。

## 复杂度
设 `n` 为 `nums` 的长度。哈希查询和写入平均为 `O(1)`，整趟扫描平均时间 `O(n)`；极端哈希冲突下最坏时间 `O(n²)`。哈希表最多记录 `n` 个不同的键，额外空间 `O(n)`。

## 易错点
- 不要先写入当前元素再查补数，否则 `target` 等于当前值的两倍时可能误用同一个下标。
- 查询时用 `find` 而非 `operator[]`；后者会为不存在的键插入默认值。下标 `0` 也是合法结果，不能把它当作未命中。
- 本题范围内补数的绝对值最多为 `2 × 10⁹`，适合 32 位有符号 `int`；若推广到完整 `int` 值域，需要用更宽的类型计算补数。

## 总结
把配对条件改写成补数查询：每次只查已扫描的前缀，既省掉第二层循环，又自然保证两下标不同。

## 复盘
复习时用 `[3, 3]`、目标 `6` 手推「先查再存」，再用题面之外的 `[3, 4]`、目标 `6` 检查不会把下标 `0` 用两次，也不会在无解时返回伪造下标。
