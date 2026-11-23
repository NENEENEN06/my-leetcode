class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indexByValue;
        vector<int> answerIndices;
        int numCount = nums.size();
        for (int currentIndex = 0; currentIndex < numCount; currentIndex++) {
            auto complementEntry = indexByValue.find(target - nums[currentIndex]);
            if (complementEntry == indexByValue.end()) {
                indexByValue[nums[currentIndex]] = currentIndex;
            } else {
                answerIndices.push_back(complementEntry->second);
                answerIndices.push_back(currentIndex);
                break;
            }
        }
        return answerIndices;
    }
};
