class Solution {
public:
   bool uniformArray(vector<int>& nums1) {
       int n=nums1.size();
       int minx=1e9;
       int cnt=0;
       for(int i=0;i<n;++i){
           if(nums1[i]%2){++cnt;}
           minx=min(minx,nums1[i]);
       }
       if(minx%2==0&&cnt){return false;}
       return true;
   }
};
