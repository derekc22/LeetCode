from typing import List
import math

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        
        """
        https://www.youtube.com/watch?v=LPFhl65R7ww
        https://chatgpt.com/share/6896ea7d-e19c-8000-bbc8-9daf04040b37
        """
        
        # Ensure numsx is the smaller array
        numsx, numsy = (nums1, nums2) if len(nums1) < len(nums2) else (nums2, nums1)

        Nx, Ny = len(numsx), len(numsy)
        N = Nx + Ny
        N_half = (N + 1) // 2  # left side will have N_half elements if N is even and N_half+1 elements if N is odd

        start, end = 0, Nx  # search on counts of elements taken from numsx
        while start <= end:
            nx = (start + end) // 2           # take nx elements from numsx
            ny = N_half - nx               # take ny elements from numsy

            # Left and right values around the cuts, with sentinels
            Lx = float("-inf") if nx == 0 else numsx[nx - 1]
            Rx = float("inf")  if nx == Nx else numsx[nx]

            Ly = float("-inf") if ny == 0 else numsy[ny - 1]
            Ry = float("inf")  if ny == Ny else numsy[ny]

            if Lx <= Ry and Ly <= Rx:
                if N % 2 == 1:
                    return float(max(Lx, Ly))
                return (max(Lx, Ly) + min(Rx, Ry)) / 2
            elif Lx > Ry:
                end = nx - 1
            else:
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