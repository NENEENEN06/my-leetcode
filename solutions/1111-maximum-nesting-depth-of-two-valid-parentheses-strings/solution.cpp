class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n=seq.size();
        vector<int>res(n,0);
        for(int i=1;i<n;i++){
            if(seq[i]==seq[i-1]){
                res[i]=1-res[i-1];
            }
            else{
                res[i]=res[i-1];
            }
        }
        return res;
    }
};
