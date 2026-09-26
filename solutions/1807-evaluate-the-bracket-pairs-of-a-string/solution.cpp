class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
            unordered_map<string,string>mp;
            string res;
            for(auto &row : knowledge){
                mp[row[0]]=row[1];
            }
            int len=s.size();
            for(int i=0;i<len;i++){
                if(s[i]=='('){
                    i++;
                    string tmp;
                    for(;s[i]!=')';i++){
                        tmp+=s[i];
                    }
                    auto it=mp.find(tmp);
                    if(it!=mp.end()){
                        res+=it->second;
                    }
                    else{
                        res+='?';
                    }
                }
                else{
                    res+=s[i];
                }
            }
            return res;
    }
};
