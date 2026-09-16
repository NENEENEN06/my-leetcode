class Solution {
public:
    int numberOfSets(int n, int k) {
        int mod=1e9+7;
        int ans=0;
        vector<vector<int>>dp(n+1,vector<int>(k+1,0));        vector<vector<int>>f(n+1,vector<int>(k+1,0));

        for(int i=1;i<=n;i++){
            f[i][0]=1;
            for(int j=1;j<i&&j<=k;j++){
               dp[i][j]=f[i][j-1]+dp[i-1][j];
               f[i][j]=dp[i-1][j]+f[i-1][j];
               dp[i][j]%=mod;
               f[i][j]%=mod;
            }
        }
        ans=dp[n][k]+f[n][k];
        ans%=mod;
        return ans;
    }
};
