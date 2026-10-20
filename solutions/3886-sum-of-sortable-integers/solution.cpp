class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n=nums.size();
        int res=0;
        vector<int>ordered_nums=nums;
        sort(ordered_nums.begin(),ordered_nums.end());
        unordered_set<int>k_set;
        for(int i=1;i<=sqrt(n);i++){
            if(n%i==0){
                k_set.insert(i);
                k_set.insert(n/i);
            }
        }
        for(int k:k_set){
            bool flag=true;
            for(int left=0;left<n;left+=k){
                bool tmp=false;
                for(int off=0;off<k;off++){
                    for(int pos=0;pos<k;pos++){
                        if(nums[left+pos]!=ordered_nums[left+(pos+off)%k]){
                            break;
                        }
                        if(pos==k-1){
                            tmp=true;
                        }
                    }
                    if(tmp){
                        break;
                    }
                }
                if(!tmp){
                    flag=false;
                    break;
                }
            }
            if(flag){
                res+=k;
            }
        }
        return res;
    }
};
