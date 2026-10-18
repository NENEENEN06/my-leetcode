class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int totalOne=0;
        int n=s.size();
        vector<int>cntZero(2,0);
        int cnt=0;
        for(int i=0;i<n;i++){
            if(s[i]=='1'){
                totalOne++;
                continue;
            }
            cntZero[0]=cntZero[1];
            cntZero[1]=1;
            while(i+1<n&&s[i+1]=='0'){
                cntZero[1]++;
                i++;
            }
            cnt=max(cnt,cntZero[0]+cntZero[1]);
        }
        if(cntZero[0]==0){
            return totalOne;
        }
        return cnt+totalOne;
    }
};
