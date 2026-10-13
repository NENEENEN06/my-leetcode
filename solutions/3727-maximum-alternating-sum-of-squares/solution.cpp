class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        long long res=0;
        sort(nums.begin(),nums.end(),[](int a,int b){
            return abs(a)>abs(b);
        });
        int n=nums.size();
        for(int i=0;i<n;i++){
            if(i<(n+1)/2){
                res+=nums[i]*nums[i];
            }
            else{
                res-=nums[i]*nums[i];
            }
        }
        return res;
    }
};
