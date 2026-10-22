// 2265. Count Nodes Equal to Average of Subtree
// 后序遍历返回 (子树节点数, 子树元素和)，回溯时顺手算出平均值，再与当前节点值比较。
class Solution {
public:
    int ans = 0;
    pair<int, int> dfs(TreeNode* node) {
        if (node == nullptr) {
            return {0, 0};
        }
        auto [leftSize, leftSum] = dfs(node->left);
        auto [rightSize, rightSum] = dfs(node->right);
        int size = leftSize + rightSize + 1;
        int sum = leftSum + rightSum + node->val;
        // 整数除法即题面要求的平均值，相等就计入答案
        if (sum / size == node->val) {
            ans++;
        }
        return {size, sum};
    }
    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
