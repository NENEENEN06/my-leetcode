class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n=nums.size();
        if(n==1){return 0;}
        int base_pos=0;
        bool flag=(nums[1]==1)?true:false;
        for(int i=1;i<n;i++){
            if(nums[i]==0){
                base_pos=i;
                flag=(nums[(i+1)%n]==1)?true:false;
                continue;
            }
            else if(nums[i]==n-1){
                continue;
            }
            if((nums[i]-nums[i-1])*(nums[(i+1)%n]-nums[i])!=1){
                return -1;
            } 
        }
        if(flag){
            return min(base_pos,n-base_pos+2);
        }
        else{
            base_pos=(1+base_pos)%n;
            return min(base_pos,n-base_pos)+1;
        }
    }
};