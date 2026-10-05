class Solution {
public:
    int scoreOfParentheses(string s) {
        int res=0;
        int left=0;
        int n=s.size();
        for(int i=0;i<n;i++){
            if(s[i]=='('){
                left++;
            }
            if(s[i]==')'){
                left--;
                if(s[i-1]=='('){
                    res+=pow(2,left);
                }
            }
        }
        return res;
    }
};
