class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int>maxVal(n,nums[0]);
        vector<int>minVal(n,nums[n-1]);
        for(int i=1;i<n;++i){
            maxVal[i]=max(maxVal[i-1],nums[i]);
            minVal[n-i-1]=min(minVal[n-i],nums[n-i-1]);
        }
        for(int i=0;i<n;++i){
            if(maxVal[i]-minVal[i]<=k){
                return i;
            }
        }
        return -1;
    }
};
