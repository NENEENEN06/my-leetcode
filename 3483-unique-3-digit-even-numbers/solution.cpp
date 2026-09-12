class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int cnt[10]={0};
        int ans=0;
        for(auto i:digits){
            cnt[i]++;
        }
        for(int i=1;i<=9;++i){
            if(!cnt[i]){continue;}
            cnt[i]--;
            for(int j=0;j<=9;++j){
                if(!cnt[j]){continue;}
                cnt[j]--;
                for(int k=0;k<=9;k+=2){
                    if(cnt[k]){ans++;}
                }
                cnt[j]++;
            }
            cnt[i]++;
        }
        return ans;
    }
};
