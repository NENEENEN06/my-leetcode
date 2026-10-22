# 3121. Count the Number of Special Characters II

- Difficulty: Medium
- Topics: Hash Table, String
- Language: C++
- 题目链接: https://leetcode.cn/problems/count-the-number-of-special-characters-ii/

## 题目

给定字符串 `word`（只含大小写英文字母），统计"特殊字母"的个数。

某个字母是特殊的，需要同时满足：

1. 小写和大写形式都在 `word` 中出现过；
2. 该字母的**所有小写出现**都排在其**所有大写出现**之前。

返回特殊字母的个数。

## 我的思路

只关心 26 个字母在串里的两个位置，所以扫一遍把所有需要的信息压进一张哈希表：

- 遍历 `word`，对每个字符写 `lastIdx[c] = i`，但**不是无条件覆盖**：
  - 遇到小写字母（`word[i] >= 'a'`）时总是覆盖 → 表里存的是该小写字母的**最后一次出现位置**；
  - 遇到大写字母时只在表里还没有它时才写入（`lastIdx.find(ch) == lastIdx.end()`）→ 表里存的是该大写字母的**第一次出现位置**。

这样一来，一个小写字母的「最后一次位置」和一封大写字母的「第一次位置」比较，就能一次性判断"所有小写是否都在所有大写之前"：只要 `lastLower < firstUpper`，中间就不存在小写排在大写后面的情况。

最后枚举 `A`~`Z`，两种形式都在表里且 `lastIdx[大写] > lastIdx[小写]`（即大写首次出现晚于小写末次出现）时计数加一。

关键点在于"小写存最后、大写存第一次"，两种方向相反的最值用同一个循环顺手拿到，不需要分别正反扫两遍。

## 代码

```cpp
// 3121. Count the Number of Special Characters II
// 小写字母只看最后一次出现、大写字母只看第一次出现，先记位置再逐字母比较前后顺序。
class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_map<char, int> lastIdx;   // 小写记最后出现位置，大写记第一次出现位置
        int res = 0;
        int n = word.size();
        for (int i = 0; i < n; i++) {
            // 小写无条件覆盖成最新位置；大写只在未记录时写入，即保留第一次
            if (word[i] >= 'a' || lastIdx.find(word[i]) == lastIdx.end()) {
                lastIdx[word[i]] = i;
            }
        }
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            if (lastIdx.find(ch) == lastIdx.end() || lastIdx.find(ch - 'A' + 'a') == lastIdx.end()) {
                continue;   // 大小写没同时出现，不可能构成特殊字符
            } else if (lastIdx[ch] > lastIdx[ch - 'A' + 'a']) {
                res++;   // 小写最后出现早于大写首次出现，顺序满足
            }
        }
        return res;
    }
};
```

## 代码分析

- 正确性：正确
- 关键实现：`word[i] >= 'a'` 判断小写（字母表里小写 ASCII 都大于 `'a'`），小写无条件覆盖、大写只写首次，方向相反存进同一张表
- 潜在 Bug：这道题保证 `word` 只含英文字母，所以 `>= 'a'` 足以区分大小写；若输入混入其它字符（如数字、`[` 等 ASCII 大于 `'a'` 的符号），判断会失效，稳妥写法是 `islower(word[i])`
- 可以改进的地方：可以把 `unordered_map` 换成两个长度 26 的数组（或一张 52 槽的表），省掉哈希开销；判断条件也可写成 `lastIdx[ch] > lastIdx[ch-'A'+'a']` 保持原样即可，逻辑已经很直白

## 复杂度

- 时间复杂度：O(n + 26) = O(n)，一次线性扫描加一次 26 字母枚举，哈希表查找均摊 O(1)
- 空间复杂度：O(1)（本质最多 52 个键）；若按容器规模记账，可视为 O(Σ)，Σ 为字符集大小

## 易错点

- 大小写的位置方向必须相反：小写要的是**最后**一次，大写要的是**第一次**，写反（比如都存首次）会把 `aAbB` 这类判错
- 只出现一种形式的字母要跳过，不能因为表里有它就计数
- 题目是 II 版（要求所有小写都在所有大写之前），和 I 版（只要求存在一对相邻的大小写）不是一回事，不要套 I 版的写法
- 用 `ch - 'A' + 'a'` 转小写比 `tolower` 更明确，也避免了 locale 相关的问题

## 总结

"某字母的所有小写都在所有大写之前"等价于 `lastLower < firstUpper`。把两个相反方向的最值在**同一个循环**里分别维护（小写覆盖、大写不覆盖），是这类"顺序约束 + 字符统计"题很省事的一个套路。
