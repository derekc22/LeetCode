from typing import List
import math

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        
        N1 = len(nums1)
        N2 = len(nums2)
        N = N1 + N2
        N_half = math.floor(N/2)
        
        numsx, Nx = (nums1, N1) if (N1 <= N2) else (nums2, N2)
        numsy, Ny = (nums1, N1) if numsx != nums1 else (nums2, N2)
                
        start = 0
        end = Nx - 1 # prevent negative indices of len(numx) == 1
                            
        while True:
            nx = math.floor((start + end)/2)
            ny = N_half - (nx+1) - 1
            print(nx, ny)
                
            if nx < 0:
                nums = numsy + numsx
                return (nums[math.floor(N/2) - 1] + nums[math.floor(N/2)])/2 if N % 2 == 0 else nums[math.floor(N/2)] 

            elif ny < 0:
                nums = numsx + numsy
                return (nums[math.floor(N/2) - 1] + nums[math.floor(N/2)])/2 if N % 2 == 0 else nums[math.floor(N/2)] 
                
            x = numsx[nx]
            y = numsy[ny]
            
            if x <= numsy[ny+1] and y <= numsx[nx+1]:
                # even if N % 2 == 0 else odd
                return ( max(x, y) + min(numsx[nx+1], numsy[ny+1]) ) / 2 if N % 2 == 0 else min(numsx[nx+1], numsy[ny+1])

            elif not x < numsy[ny+1]:
                end = nx - 1
                
            elif not y < numsx[nx+1]:
                start = nx + 1
                


if __name__ == "__main__":
    sol = Solution()
    # nums1 = [1,3,8,9,15]
    # nums2 = [7,11,18,19,21,25]
    # nums1 = [1,2,3,4,5]
    # nums2 = [6,7,8,9,10,11,12,13,14,15,16,17]
    # nums1 = [1, 3, 4, 5]
    # nums2 = [2, 4, 5, 6, 7, 8]
    # nums1 = [100]
    # nums2 = [101]
    nums1 = [1, 3]
    nums2 = [2]

    print(sol.findMedianSortedArrays(nums1, nums2))


# Nx = 5
# Ny = 4
# start = 0
# end = Nx

# nx = math.floor((start + end)/2) - 1
# ny = math.floor(((Nx + Ny + 1)/2)) - (nx + 1) - 1

# print(nx+1)
# print(ny+1)