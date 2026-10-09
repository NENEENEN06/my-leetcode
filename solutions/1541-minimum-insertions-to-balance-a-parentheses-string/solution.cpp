class Solution {
public:
    int minInsertions(string s) {
        int l1=0,l2=0,l3=0;
        int flag=0;
        for(auto &ch:s){
            if(ch=='('){
                if(flag){
                    if(l1==0){
                        l2++;
                        l3++;
                    }
                    else{
                        l3--;
                        l1--;
                    }
                    flag=0;
                }
                l1++;
                l3+=2;
            }
            else if(l1>0){
                if(flag){
                    l1--;
                    l3-=2;
                    flag=0;
                }
                else{
                    flag=1;
                }
            }
            else{
                if(flag){
                    l2++;
                    flag=0;
                }
                else{
                    flag=1;
                }
            }
        }
        if(flag){
            if(l1>0){
                l3--;
            }
            else{
                l3++;
                l2++;
            }
        }
        return l3+l2;
    }
};
