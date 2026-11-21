# 3331. Find Subtree Sizes After Changes

- Difficulty: Medium
- Topics: Array, Hash Table, String, Tree, Depth-First Search
- Language: C++
- 题目链接: https://leetcode.cn/problems/find-subtree-sizes-after-changes/

## 题目

给定一棵以 `0` 为根的树，`parent[i]` 是节点 `i` 的父节点，每个节点有一个小写字母。对所有非根节点同时进行一次改挂：若原树上有同字符的严格祖先，就改挂到最近的那个，否则保留原父节点。返回改挂后每个节点的子树大小（含自身）。

## 我的思路

先用原树的邻接表做 DFS。为每个字符维护一个栈，记录当前路径上带这个字符的祖先：栈顶就是最近的同字符祖先。进入节点时先查栈顶，再把自身入栈；退出时出栈。第一遍 DFS 只更新 `parent`，不动用于遍历的原邻接表。随后用更新后的 `parent` 重建邻接表，再做一遍后序 DFS，累加每个节点的子树大小。

## 代码

```cpp
class Solution {
public:
    void updateParents(vector<int>& parent, vector<list<int>>& children,
                       unordered_map<char, stack<int>>& ancestorsByChar, string& labels, int node) {
        if (!ancestorsByChar[labels[node]].empty()) {
            parent[node] = ancestorsByChar[labels[node]].top();
        }
        ancestorsByChar[labels[node]].push(node);

        for (int child : children[node]) {
            updateParents(parent, children, ancestorsByChar, labels, child);
        }
        ancestorsByChar[labels[node]].pop();
    }

    int countSubtreeSizes(vector<list<int>>& children, int node, vector<int>& result) {
        for (int child : children[node]) {
            result[node] += countSubtreeSizes(children, child, result);
        }
        return result[node];
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string labels) {
        int nodeCount = parent.size();
        vector<list<int>> children(nodeCount);
        vector<int> result(nodeCount, 1);
        unordered_map<char, stack<int>> ancestorsByChar;
        for (int nodeIndex = 1; nodeIndex < nodeCount; nodeIndex++) {
            children[parent[nodeIndex]].push_back(nodeIndex);
        }
        updateParents(parent, children, ancestorsByChar, labels, 0);
        children.assign(nodeCount, {});
        for (int nodeIndex = 1; nodeIndex < nodeCount; nodeIndex++) {
            children[parent[nodeIndex]].push_back(nodeIndex);
        }
        countSubtreeSizes(children, 0, result);
        return result;
    }
};
```

## 代码分析

- **栈顶为什么是最近祖先**：进入节点时，仍在栈中的节点恰好来自原树上从根到其父节点的路径。祖先按深度递增入栈，离开分支时出栈，因此同字符栈顶既是严格祖先，也是最深的那个。栈为空时不修改 `parent`，根节点也因此保留 `-1`。
- **为什么等价于同时修改**：第一遍的递归完全依据旧邻接表，每个新父节点都从原树的祖先中选，前面节点的改挂不会改变后面节点的候选。对每个非根节点，无论保留还是改挂，沿新父指针走一步都会降低其在原树中的深度；因此无环，且每条父指针链最终都到达根。
- **为什么后序累加正确**：新树上不同子节点的子树互不相交，节点自身贡献 `1`，加上每个子节点已经算出的子树大小，就是该节点的完整答案。
- 代码取自力扣 Accepted 提交 `761038638`，仅调整排版和命名。

## 复杂度

- 时间复杂度：`O(n)`。建表两次、遍历两次，每遍访问 `n - 1` 条边；字符映射最多 `26` 个键。
- 空间复杂度：`O(n)`。邻接表、结果和路径栈均不超过线性规模；链形树上的递归深度也可达 `n`。

## 易错点

- 查栈顶必须在当前节点入栈前，否则每个节点都会把自己当作祖先；退出时必须出栈，避免把上一条分支的节点当成当前分支的祖先。
- 不要沿新父指针找同字符祖先。例如题目的第二组数据中，节点 `4` 改挂到 `0` 后，节点 `2` 仍须沿原路径 `2 → 4 → 1 → 0` 找到同字符的节点 `1`。
- 单节点树应直接得到 `[1]`。建表要从节点 `1` 开始，不能拿根节点的 `-1` 当数组下标；此外，这份递归实现若在本地栈限额较低的环境运行，深链可能导致栈溢出。

## 总结

找新父节点用原树，统计子树大小用新树。按字符维护路径栈，把每个节点对祖先链的搜索缩成一次查栈顶。

## 复盘

遇到「同时修改」先用多层改挂的样例检查是否读到了中间状态；遇到回溯维护路径信息，再用共享父节点的兄弟分支检查是否正确出栈。
