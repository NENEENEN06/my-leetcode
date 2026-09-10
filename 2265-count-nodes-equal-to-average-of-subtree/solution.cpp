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
