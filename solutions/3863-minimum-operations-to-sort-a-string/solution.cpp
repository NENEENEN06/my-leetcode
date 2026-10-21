class Solution {
public:
    int minOperations(string s) {
        int n=s.size();
        if(n==2&&s[0]>s[1]){
            return -1;
        }
        bool flag=true;
        int min_pos=0;
        int max_pos=n-1;
        for(int i=1;i<n;i++){
            if(flag&&s[i]<s[i-1]){
                flag=false;
            }
            min_pos=(s[i]<s[min_pos])?i:min_pos;
            max_pos=(s[n-1-i]>s[max_pos])?(n-1-i):max_pos;
        }
        if(flag){
            return 0;
        }
        if(min_pos==0||max_pos==n-1){
            return 1;
        }
        if(min_pos==n-1&&max_pos==0){
            return 3;
        }
        return 2;
    }
};
