class Solution {
public:
    bool isValid(string s) {
        stack<char>st;
        for(auto ch:s){
            if(string("([{").find(ch)!=string::npos){
                st.push(ch);
            }
            else{
                if(st.empty()||(st.top()!=ch-2&&st.top()!=ch-1)){
                    return false;
                }
                st.pop();
            }
        }
        return st.empty();
    }
};
