from typing import List
import math

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        
        N1 = len(nums1)
        N2 = len(nums2)
        N = N1 + N2
        
        numsx, Nx = (nums1, N1) if (N1 < N2) else (nums2, N2)
        numsy, Ny = (nums1, N1) if numsx != nums1 else (nums2, N2)
        
        ny = math.floor((Ny-1)/2)
        y = numsy[ny]
        
        if Nx == 0:
            return (y + numsy[ny+1])/2 if N % 2 == 0 else y
        if Nx == 1:
            x = numsx[0]
            print(x, y)
            if N % 2 == 0:
                return (y + min(x, numsy[ny-1]))/2 if x < y else (y + max(x, numsy[ny+1]))/2 if x > y else y
            else: 
                return y if x < y else numsy[ny+1] if x > numsy[ny+1] else x
        
        start = 0
        end = Nx - 1  
                
        while True:
            # subtract 1 at the end to convert to an index
            # nx = # elements from shorter arr on the LHS
            # ny = # elements from longer arr on the LHS
            nx = math.floor((start + end)/2)
            split = math.floor((Nx + Ny + 1)/2)
            ny = split - (nx + 1) - 1
            print(nx, ny)
                
            if nx < 0:
                numsy.extend(numsx)
                return (numsy[split-1] + numsy[split])/2 if N % 2 == 0 else numsy[split-1]
            elif nx == Nx - 1:
                numsx.extend(numsy)
                return (numsx[split-1] + numsx[split])/2 if N % 2 == 0 else numsx[split-1]
                
            x = numsx[nx]
            y = numsy[ny]
            
            if x <= numsy[ny+1] and y <= numsx[nx+1]:
                # even if N % 2 == 0 else odd
                return ( max(x, y) + min(numsx[nx+1], numsy[ny+1]) ) / 2 if N % 2 == 0 else max(x, y)

                
            elif x > numsy[ny]:
                end = nx - 1
                
            elif y > numsx[nx]:
                start = nx + 1
                


if __name__ == "__main__":
    sol = Solution()
    # nums1 = [1,3,8,9,15]
    # nums2 = [7,11,18,19,21,25]
    nums1 = [1,2,3,4,5]
    nums2 = [6,7,8,9,10,11,12,13,14,15,16,17]
    # nums1 = [100]
    # nums2 = [101]

    print(sol.findMedianSortedArrays(nums1, nums2))


# Nx = 5
# Ny = 4
# start = 0
# end = Nx

# nx = math.floor((start + end)/2) - 1
# ny = math.floor(((Nx + Ny + 1)/2)) - (nx + 1) - 1

# print(nx+1)
# print(ny+1)