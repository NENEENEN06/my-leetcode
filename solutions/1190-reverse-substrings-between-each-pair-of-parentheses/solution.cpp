class Solution {
public:
    string reverseParentheses(string s) {
        stack<int>st;
        string res;
        int len=s.size();
        for(int i=0;i<len;i++){
            if(s[i]=='('){
                st.push(i);
            }
            if(s[i]==')'){
                int l=st.top();
                int r=i;
                st.pop();
                reverse(s.begin()+l,s.begin()+r+1);
            }
        }
        for(int i=0;i<len;i++){
            if(s[i]!='('&&s[i]!=')'){
                res+=s[i];
            }
        }
        return res;
    }
};
