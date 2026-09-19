class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int left=0,right=0;
        int n=arr.size();
        int cnt =0;
        vector<int>dp(n+1,100001);
        int ans=100001;
        while(right<n){
            cnt+=arr[right];
            while(cnt>target){
                cnt-=arr[left];
                left++;
            }
            dp[right+1]=dp[right];
            if(cnt==target){
                ans=min(ans,dp[left]+right-left+1);
                dp[right+1]=min(dp[right],right-left+1);
            }
            right++;
        }
        return (ans==100001)?-1:ans;
        }
};
