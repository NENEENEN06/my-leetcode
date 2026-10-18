class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_map<char,int>st;
        int res=0;
        int n=word.size();
        for(int i=0;i<n;i++){
            if(word[i]>='a'||st.find(word[i])==st.end()){
                st[word[i]]=i;
            }
        }
        for(char ch='A';ch<='Z';ch++){
            if(st.find(ch)==st.end()||st.find(ch-'A'+'a')==st.end()){
                continue;
            }
            else if(st[ch]>st[ch-'A'+'a']){
                res++;
            }
        }
        return res;
    }
};
