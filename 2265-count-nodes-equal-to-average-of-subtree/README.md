# 2265. Count Nodes Equal to Average of Subtree

- Difficulty: Medium
- Topics: Tree, Depth-First Search, Binary Tree
- Language: C++
- 题目链接: https://leetcode.cn/problems/count-nodes-equal-to-average-of-subtree/

## 题目

给定二叉树根节点 `root`，统计有多少个节点满足：**该节点的值等于其子树（包含自身和全部后代）中所有节点值的平均值**。平均值定义为求和后除以节点个数再**向下取整**。

## 我的思路

- 核心思想：一次**后序 DFS**，让递归函数自底向上返回每个节点子树的 `(size, sum)`——节点个数与节点值之和，回程时顺手判断当前节点的子树平均值是否等于自身。
- 使用的数据结构：`pair<int,int>` 承载 `(size, sum)`，用 C++17 结构化绑定解包左右子树的结果；成员变量 `ans` 累加答案。
- 算法流程：
  1. 空节点返回 `{0, 0}`。
  2. 递归求左右子树的 `(size, sum)`。
  3. 合并出当前子树：`size = leftSize + rightSize + 1`，`sum = leftSum + rightSum + Node->val`。
  4. 若 `sum / size == Node->val`，则 `ans++`。
  5. 返回 `{size, sum}` 给父节点。
- 为什么这样做：子树的节点数与和，都能由左右子树的两项数据 **O(1)** 合并得到，满足可合并性，所以一趟后序遍历即可自底向上把每个子树统计出来，无需对每个节点重新遍历它的整棵子树。
- 关键状态 / 变量：`pair` 的语义是 `{size, sum}`，返回与解包的字段顺序必须一致；`ans` 是全局计数器。
- 为什么能够得到正确答案：每个节点在回程时都已拿到整棵子树的节点数与和，`sum / size` 正是题目要求的平均值；由于本题 `0 <= Node.val`，所有和与个数均非负，C++ 的整数除法等同于**向下取整**，与题意一致。

## 代码

```cpp
class Solution {
public:
    int ans=0;
    pair<int,int>dfs(TreeNode* Node){
        if(Node==nullptr){return {0,0};}
        auto [leftSize,leftSum]=dfs(Node->left);
        auto [rightSize,rightSum]=dfs(Node->right);
        int size=leftSize+rightSize+1;
        int sum=leftSum+rightSum+Node->val;
        if(sum/size==Node->val){ans++;}
        return {size,sum};
    }
    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
```

## 代码分析

- 正确性：正确。
- 关键实现：DFS 返回 `(size, sum)`，在回程合并出当前子树统计量后立即判等，一趟遍历完成统计与计数。
- 潜在 Bug：`ans` 是成员变量，而 `averageOfSubtree` 内部没有重置它。LeetCode 每个测试用例会新建 `Solution` 实例，因此不受影响；但若在**同一个对象**上多次调用该方法，答案会累加。另外，整数除法只有在被除数非负时才等价于向下取整——本题 `0 <= Node.val <= 1000` 保证成立；若值域含负数，C++ 除法向零截断会与题意不符。
- 可以改进的地方：把 `ans` 改为参数（引用）传回或作为返回值累加，消除对成员状态的依赖；也可把判等与返回合并表达，但当前写法在可读性上已经足够。

## 复杂度

- 时间复杂度：O(n)。每个节点恰好被访问一次，合并与判等均为 O(1)。
- 空间复杂度：O(h)，h 为树高，即递归调用栈深度；最坏（链状树）为 O(n)，平衡树为 O(log n)。除递归栈外无额外空间。

## 易错点

- `pair` 的字段顺序容易写反：返回的是 `{size, sum}`，解包时也要按 `(size, sum)` 对应，交换会算出错误结果。
- 平均值要**向下取整**：本解法依赖非负整数除法天然向下取整；一旦值域含负数就不能直接用 `/`。
- 判断的是「节点值 == **子树**平均值」，子树包含节点自身，所以 `size` 要 `+1`、`sum` 要加上当前 `Node->val`，别漏掉自己。
- 空节点基准 `{0, 0}` 要处理正确，避免对空子树做除法。
- 成员变量 `ans` 存在跨调用状态残留（见「代码分析」），多测共用一个对象时会错。

## 总结

「**子树统计量可合并**」是这类题的通用套路：让 DFS 返回子树的聚合信息（这里是 `size` 与 `sum`），在回程时用子节点的信息 O(1) 拼出父节点的信息，并顺手完成判定。相比对每个节点各跑一次子树遍历的 O(n²) 暴力，一趟后序遍历即可降到 O(n)。同样的结构可迁移到「子树最大/最小平均值」「值等于子节点值之和的节点数量」等题。

## 复盘

- 关键突破点：意识到「平均值」需要的是子树的**和**与**个数**两项，二者都能由子问题合并而来，于是把它设计成后序 DFS 的返回值。
- 下次看到什么特征应该想到这个算法：题目要求对每个节点/子树统计聚合量（和、个数、最值），且聚合量可由左右子树合并——优先考虑「DFS 返回聚合信息 + 回程处理」的模板。
