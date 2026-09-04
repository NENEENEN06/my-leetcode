# 0003. Longest Substring Without Repeating Characters

- Difficulty: Medium
- Topics: Hash Table, String, Sliding Window
- Language: C
- 题目链接: https://leetcode.cn/problems/longest-substring-without-repeating-characters/

## 题目

给定一个字符串 `s`，找出其中不含重复字符的最长子串的长度。

## 我的思路

- 核心思想：滑动窗口。窗口 `[left, right]` 始终是一个不含重复字符的子串，用计数数组 `flag` 记录窗口中每个字符出现的次数。
- 使用的数据结构：`flag[127]` 计数数组，配合 `left`、`right` 两个指针。
- 算法流程：
  1. `right` 不断向右扩展；若 `s[right]` 在窗口中还没出现过（`flag[s[right]] == 0`），就把它加入窗口并更新答案。
  2. 一旦 `s[right]` 在窗口中已经出现（`flag[s[right]] == 1`），就从 `left` 开始不断收缩窗口，逐个移出左侧字符并把计数减一，直到窗口里那个重复的字符被清掉。
  3. 重复上述过程直到 `right` 走到字符串末尾，返回过程中记录的最大窗口长度 `ans`。
- 为什么这样做：当出现重复时，只有把窗口左边界推进到重复字符第一次出现位置之后，才可能继续形成更长的无重复子串；每次扩展/收缩都维护“窗口内无重复字符”的不变量。
- 关键状态 / 变量：`left`（窗口左边界）、`right`（窗口右边界）、`ans`（历史最大长度）。
- 为什么能够得到正确答案：枚举了每个以不同 `right` 结尾的最长无重复子串，答案取其中的最大值，即覆盖了所有可能的最长子串。

## 代码

```c
int lengthOfLongestSubstring(char* s) {
    int flag[127]={0};
    int left=0,right=0;
    int ans=0;
    int len=strlen(s);
    while(right<len){
        while(flag[s[right]]==0&&right<len){
            ans=(ans>right-left+1)?(ans):(right-left+1);
            flag[s[right++]]++;
        }
        while(flag[s[right]]==1&&left<right){
            flag[s[left++]]--;
        }
    }
    return ans;
}
```

## 代码分析

- 正确性：正确。
- 关键实现：`flag` 用字符的 ASCII 值做下标做频数统计；`right` 扩展时加入字符，`left` 收缩时移除字符，全程保证窗口内字符互不重复。
- 潜在 Bug：无明显逻辑错误。需要留意两点：一是数组大小为 127，只能覆盖 ASCII 字符，题目输入恰好满足；二是内层 `while(flag[s[right]]==0&&right<len)` 在 `right==len` 时会先读 `s[len]`（即 `'\0'`），因为 `flag[0]` 恒为 0，所以能安全退出，不构成越界访问（`'\0'` 位于字符串数组内）。
- 可以改进的地方：若字符集更大（比如包含中文或 Unicode），应改用哈希表/大小为 256 的数组；也可以把 `ans` 更新写成 `max` 风格提升可读性。

## 复杂度

- 时间复杂度：O(n)。`right` 每步只会前进，`left` 总共最多前进 n 次，每个字符最多被加入和移出窗口各一次。
- 空间复杂度：O(1)。只使用了固定大小的计数数组。

## 易错点

- 空字符串应返回 0，本代码 `len == 0` 时直接跳过循环返回 0，正确。
- 条件判断顺序：读 `s[right]` 前要保证 `right < len`；本题写法虽然依赖 `'\0'` 恰好让 `flag[0]==0`，逻辑上等价于先判边界，但更稳妥的写法是先把 `right<len` 放前面。
- 窗口收缩时记得同步把 `flag[s[left]]` 减一，漏减会导致后续判断错误。
- 字符集范围：若字符超出 ASCII，固定数组会越界。

## 总结

经典滑动窗口模板：右指针负责扩张并维护计数，遇到重复时左指针收缩，直到窗口重新合法；答案在扩张阶段实时更新。判断“子串内是否重复”用频数数组/哈希即可。

## 复盘

- 我哪里容易想错：容易把收缩一步到位写成 `left = 上次出现位置 + 1` 而忘记同步更新计数，导致后续状态错乱。
- 关键突破点：抓住“窗口内无重复字符”这个不变量，重复出现时只收缩到刚能去掉旧重复的位置。
- 下次看到什么特征应该想到这个算法：看到“最长子串/子数组 + 无重复/至多 k 种字符”等限制，优先想滑动窗口。
