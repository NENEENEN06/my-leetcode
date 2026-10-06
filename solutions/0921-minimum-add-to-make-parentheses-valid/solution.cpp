class Solution {
public:
    int minAddToMakeValid(string s) {
        int l1=0,l2=0;
        for(auto &ch:s){
            if(ch=='('){
                l1++;
            }
            else if(l1>0){
                l1--;
            }
            else{
                l2++;
            }
        }
        return l1+l2;
    }
};
