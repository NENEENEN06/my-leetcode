class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n=nums.size();
        vector<vector<long long>>result(2,vector<long long>(k,0));
        vector<long long>ans(k,0);
        result[0][nums[0]%k]++;
        ans[nums[0]%k]++;
        for(int i=1;i<n;i++){
            nums[i]%=k;
            for(int j=0;j<k;j++){
                result[i%2][(j*nums[i])%k]+=result[(i-1)%2][j];
                result[(i-1)%2][j]=0;
            }
            result[i%2][nums[i]]++;
            for(int j=0;j<k;j++){
                ans[j]+=result[i%2][j];
            }
        }
        return ans;
    }
};
