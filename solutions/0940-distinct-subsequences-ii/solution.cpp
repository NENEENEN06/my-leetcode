class Solution {
public:
    int distinctSubseqII(string s) {
        int mod=1e9+7;
        int ans=1;
        int sLen=s.size();
        vector<int>dp(sLen,0);
        dp[0]=1;
        for(int i=1;i<sLen;++i){
            for(int j=i-1;j>=0;--j){
                dp[i]+=dp[j];
                dp[i]%=mod;
                if(s[i]==s[j]){break;}
                if(j==0){dp[i]++;}
            }
            ans+=dp[i];
            ans%=mod;
        }
        return ans;
    }
};
