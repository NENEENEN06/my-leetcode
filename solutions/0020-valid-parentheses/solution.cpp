class Solution {
public:
    bool isValid(string s) {
        stack<char>st;
        map<char,char>mp={
            {')','('},
            {'}','{'},
            {']','['}
        };
        for(auto ch:s){
            if(mp.find(ch)==mp.end()){
                st.push(ch);
            }
            else{
                if(st.empty()||st.top()!=mp[ch]){
                    return false;
                }
                else{
                    st.pop();
                }
            }
        }
        return st.empty();
    }
};
