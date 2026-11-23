# 1352. Product of the Last K Numbers

- Difficulty: Medium
- Topics: Array, Math, Design, Data Stream, Prefix Sum
- Language: C++
- 题目链接: https://leetcode.com/problems/product-of-the-last-k-numbers/

## 题目

维护一个整数流，支持追加 `num` 和查询最后 `k` 个数的乘积。每次查询都保证至少已有 `k` 个数，且任意连续子段的乘积都在 32 位整数范围内。

## 我的思路

只维护最近一个 `0` 之后的前缀积，用 `products[0] = 1` 表示空前缀。加入非零数时，在当前末尾的前缀积上乘一次；加入 `0` 时把 `products` 重置为 `{1}`。查询时先判断最后 `k` 个数是否跨过最近的 `0`：跨过就返回 `0`，否则用两个前缀积相除。

## 代码

来源：力扣中国站 [Accepted 提交 #761246473](https://leetcode.cn/submissions/detail/761246473/)，2026-11-23 16:23:36 UTC+8，C++。仅调整排版和注释。

```cpp
class ProductOfNumbers {
public:
    vector<int> products = {1};

    ProductOfNumbers() {
    }

    void add(int num) {
        if (num) {
            products.push_back(products.back() * num);
        } else {
            // 乘积跨过这个 0 时一定为 0，不必再保存此前的前缀。
            products = {1};
        }
    }

    int getProduct(int k) {
        if (k < products.size()) {
            return products.back() / products[products.size() - k - 1];
        } else {
            return 0;
        }
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
```

## 代码分析

- **不变量：** 设最近一次遇到 `0` 之后已有 `m` 个数（从未遇到 `0` 时用整个流）。`products` 有 `m + 1` 项，第 `i` 项是这段中前 `i` 个数的乘积，且第 0 项为 `1`。初始化和遇到 `0` 后都有 `m = 0`；追加非零数时，旧前缀都不受影响，新前缀正好是旧末项乘上新数，因此不变量一直成立。
- **查询正确性：** `k < products.size()` 等价于 `k <= m`。此时查询完全落在非零段内，末项 `products[m]` 等于 `products[m - k]` 乘上所求乘积，所以除法精确且分母非零。若 `k > m`，题目保证已有 `k` 个数，故查询必然包含最近一次加入的 `0`，返回 `0` 正确。
- **边界：** `k = m` 时分母下标为 `0`，结果是整段非零积；刚加入 `0` 时 `m = 0`，合法查询的 `k` 都至少为 `1`。存下的每个非空前缀也是原流中的连续子段，因此题面的乘积上界适用于构造前缀积时的乘法。

## 复杂度

- 时间：`getProduct` 为 O(1)。`add` 均摊 O(1)：非零追加的扩容成本由 `vector` 均摊；即使把遇零时丢弃旧元素的成本逐项计算，每项也至多被丢弃一次。
- 空间：峰值 O(L + 1)，其中 L 为历史最长连续非零段的长度。重置后的有效元素只有一个，但 `vector` 可能保留先前的容量。

## 易错点

- `products.size()` 包含哨兵 `1`，查询条件应是 `k < products.size()`，不是 `k <= products.size()`；`k` 恰好等于大小时，查询已经包含 `0`。
- 应先判断是否跨零，再计算 `products.size() - k - 1`。否则在无符号下标运算里可能下溢。

## 总结

遇零切段，段内用前缀积相除；每次查询只需一次边界判断与至多一次除法。

## 复盘

遇到只追加、频繁查后缀的题，先想怎样从前缀状态抵消掉不需要的部分。乘积遇到 `0` 无法直接抵消，就把它当成分界。复查条件时，优先手算「恰好查完整个非零段」和「再多查一项」这两个相邻边界。
