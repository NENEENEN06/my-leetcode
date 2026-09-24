class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int n=nums.size();
        for(int i=0;i<n;i++){
            int num=0;
            while(nums[i]){
                num+=nums[i]%10;
                nums[i]/=10;
            }
            if(num==i){
                return i;
            }
        }
        return -1;
    }
};
