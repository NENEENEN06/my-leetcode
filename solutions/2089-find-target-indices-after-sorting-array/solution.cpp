class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        vector<int>res;
        int n=nums.size();
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(nums[i]>nums[j]){
                    int tmp=nums[i];
                    nums[i]=nums[j];
                    nums[j]=tmp;
                }
            }
            if(nums[i]==target){
                res.push_back(i);
            }
            if(nums[i]>target){
                break;
            }
        }
        return res;
    }
};
