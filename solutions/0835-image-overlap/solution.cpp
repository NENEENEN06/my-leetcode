class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n=img1.size();
        int ans=0;
        for(int i=1-n;i<n;i++){
            for(int j=1-n;j<n;j++){
                int cnt=0;
                for(int x=0;x+i<n&&x<n;x++){
                    if(x+i<0){continue;}
                    for(int y=0;y+j<n&&y<n;y++){
                        if(y+j<0){continue;}
                        if(img1[x+i][y+j]==1&&img2[x][y]==1){
                            cnt++;
                        }
                    }
                }
                ans=max(cnt,ans);
            }
        }
        return ans;
    }
};
