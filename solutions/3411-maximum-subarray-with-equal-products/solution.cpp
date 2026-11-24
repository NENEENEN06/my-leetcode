class Solution {
public:
    int maxLength(vector<int>& nums) {
        int primes[] = {2, 3, 5, 7};
        int bestLength = 0;
        int arrayLength = nums.size();
        vector<unordered_map<int, int>> factorExponents(11);
        for (int scanIndex = 2; scanIndex <= 10; scanIndex++) {
            int remainingValue = scanIndex;
            for (int &prime : primes) {
                while (remainingValue % prime == 0) {
                    factorExponents[scanIndex][prime]++;
                    remainingValue /= prime;
                }
            }
        }
        for (int scanIndex = 0; scanIndex < arrayLength - bestLength; scanIndex++) {
            unordered_map<int, int> productExponents = factorExponents[nums[scanIndex]];
            unordered_map<int, int> gcdExponents = factorExponents[nums[scanIndex]];
            unordered_map<int, int> lcmExponents = factorExponents[nums[scanIndex]];
            for (int rightIndex = scanIndex + 1; rightIndex < arrayLength; rightIndex++) {
                bool isProductEquivalent = true;
                for (int &prime : primes) {
                    productExponents[prime] += factorExponents[nums[rightIndex]][prime];
                    gcdExponents[prime] = min(gcdExponents[prime], factorExponents[nums[rightIndex]][prime]);
                    lcmExponents[prime] = max(lcmExponents[prime], factorExponents[nums[rightIndex]][prime]);
                    if (productExponents[prime] != gcdExponents[prime] + lcmExponents[prime]) {
                        isProductEquivalent = false;
                    }
                }
                if (isProductEquivalent) {
                    bestLength = max(bestLength, rightIndex - scanIndex + 1);
                }
            }
        }
        return bestLength;
    }
};
