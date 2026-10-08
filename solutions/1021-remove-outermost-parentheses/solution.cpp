class Solution {
public:
    string removeOuterParentheses(string s) {
        string res;
        int left=0;
        for(auto ch:s){
            if(ch=='('){
                left++;
                if(left!=1){
                    res+=ch;
                }
            }
            else{
                left--;
                if(left!=0){
                    res+=ch;
                }
            }
        }
        return res;
    }
};
