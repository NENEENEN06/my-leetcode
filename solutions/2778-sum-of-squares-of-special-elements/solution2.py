class Solution:
    def sumOfSquares(self, nums: List[int]) -> int:
        return sum(nums[i]**2 for i in range(len(nums)) if len(nums)%(i+1)==0)
