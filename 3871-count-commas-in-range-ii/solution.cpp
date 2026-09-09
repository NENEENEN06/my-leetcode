class Solution {
public:
    long long countCommas(long long n) {
        long long ans=0;
        long long a=1000;
        while(a<=n){
            ans+=n-a+1;
            a*=1000;
        }
    return ans;
    }
};
