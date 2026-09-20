class Solution {
public:
    int reverseDegree(string s) {
        int ans=0;
        int n=s.size();
        for(int i=0;i<n;i++){
            ans+=(i+1)*('z'+1-s[i]);
        }
        return ans;
    }
};
