class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        string res(num,'0');
        for(int i=0;i<num;i++){
            if(sum>9){
                res[i]+=9;
                sum-=9;
            }
            else{
                res[i]+=sum;
                sum=0;
                break;
            }
        }
        if(sum){
            return "";
        }
        return res;
    }
};
