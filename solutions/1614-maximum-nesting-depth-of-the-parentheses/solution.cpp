class Solution {
public:
    int maxDepth(string s) {
        int tmp=0;
        int ans=0;
        for(auto &ch:s){
            if(ch=='('){
                ans=(++tmp>ans)?tmp:ans;
            }
            if(ch==')'){
                tmp--;
            }
        }
        return ans;
    }
};
