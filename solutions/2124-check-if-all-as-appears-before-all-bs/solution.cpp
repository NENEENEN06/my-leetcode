class Solution {
public:
    bool checkString(string letters) {
        return letters.find("ba") == string::npos;
    }
};
