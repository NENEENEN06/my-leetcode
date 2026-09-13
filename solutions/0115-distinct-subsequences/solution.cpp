class Solution {
public:
   int numDistinct(string s, string t) {
       int sLen=s.size();
       int tLen=t.size();
       vector<vector<unsigned long long>>dp(sLen,vector<unsigned long long>(tLen,0));
       for(int i=0,j=0;i<sLen;++i){
           if(s[i]==t[0]){j++;}
           dp[i][0]=j;
       }
       for(int i=1;i<sLen;++i){
           for(int j=1;j<tLen;++j){
               dp[i][j]=dp[i-1][j];
               if(s[i]==t[j]){
                   dp[i][j]+=dp[i-1][j-1];
               }
           }
       }
       return dp[sLen-1][tLen-1];
   }
};
