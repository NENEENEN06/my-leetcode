class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string>res;
        queue<pair<string,int>>q;
        q.push({"(",1});
        while(!q.empty()){
            auto [st,l]=q.front();
            q.pop();
            int len=st.size();
            if(len==2*n&&l==0){
                res.push_back(st);
            }
            if(len<2*n){
                if(l<=n&&l>0){
                    q.push({st+')',l-1});
                }
                if(l<n&&l>=0){
                    q.push({st+'(',l+1});
                }
            }
        }
        return res;
    }
};
