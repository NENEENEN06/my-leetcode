int lengthOfLongestSubstring(char* s) {
    int flag[127]={0};
    int left=0,right=0;
    int ans=0;
    int len=strlen(s);
    while(right<len){
        while(flag[s[right]]==0&&right<len){
            ans=(ans>right-left+1)?(ans):(right-left+1);
            flag[s[right++]]++;
        }
        while(flag[s[right]]==1&&left<right){
            flag[s[left++]]--;
        }
    }
    return ans;
}
