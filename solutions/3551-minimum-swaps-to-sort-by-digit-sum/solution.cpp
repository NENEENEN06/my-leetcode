class Solution {
public:
    int digitSum(int num){
        int res=0;
        while(num){
            res+=num%10;
            num/=10;
        }
        return res;
    }
    int minSwaps(vector<int>& nums) {
        vector<pair<int,int>>ordered_nums;
        unordered_map<int,int>pos;
        int n=nums.size();
        int res=0;
        for(int i=0;i<n;i++){
            ordered_nums.push_back({nums[i],digitSum(nums[i])});
            pos[nums[i]]=i;
        }
        sort(ordered_nums.begin(),ordered_nums.end(),[](auto a,auto b){
            return a.second!=b.second?a.second<b.second:a.first<b.first;
        });
        for(int i=0;i<n;i++){
            if(nums[i]==ordered_nums[i].first){continue;}
            pos[nums[i]]=pos[ordered_nums[i].first];
            nums[pos[ordered_nums[i].first]]=nums[i];
            res++;
        }
        return res;
    }
};
