class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        
        numMap = {}

        for i, curr in enumerate(nums):
            need = target-curr

            if need in numMap:
                return [i, numMap[need]]
            
            else:
                numMap[curr] = i


if __name__ == "__main__":

    arr = [2, 7, 11, 15]
    target = 9

    sol = Solution()
    print(sol.twoSum(arr, target))