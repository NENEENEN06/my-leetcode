class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        int cnt[32]={0};
        int res=0;
        const int mod=1e9+7;
        for(auto &num:nums){
            for(int i=0;i<32;i++){
                if(num&(1<<i)){
                    cnt[i]++;
                }
            }
        }
        for(int i=0;i<k;i++){
            long long tmp=0;
            for(int j=0;j<32;j++){
                if(cnt[j]){
                    cnt[j]--;
                    tmp+=1<<j;
                    tmp%=mod;
                }
            }
            res+=(tmp*tmp)%mod;
            res%=mod;
        }
        return res;
    }
};
