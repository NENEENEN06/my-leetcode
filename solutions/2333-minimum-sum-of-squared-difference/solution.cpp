class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long res=0;
        int n=nums1.size();
        vector<long long>nums(n);
        for(int i=0;i<n;i++){
            nums[i]=abs(nums1[i]-nums2[i]);
        }
        long long k=k1+k2;
        sort(nums.begin(),nums.end(),greater<long long>());
        nums.push_back(0);
        long long cnt=0;
        int pos=0;
        while(pos<n){
            cnt+=nums[pos];
            if(cnt-nums[pos+1]*(pos+1)>k){
                k-=cnt-nums[pos]*(pos+1);
                break;
            }
            pos++;
        }
        if(pos==n){
            return 0;
        }
        for(int i=0;i<n;i++){
            if(i<=pos){
                nums[i]=nums[pos]-k/(pos+1);
                if(i<k%(pos+1)){
                    nums[i]--;
                }
            }
            res+=nums[i]*nums[i];
        }
        return res;
    }
};
