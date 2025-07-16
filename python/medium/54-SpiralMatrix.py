
class Solution:
    # def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
    def spiralOrder(self, matrix):
        
        m = len(matrix)
        n = len(matrix[0])
        numel = m*n
        
        top_ptr = 0
        bottom_ptr = m-1
        left_ptr = 0
        right_ptr = n-1
        
        direction = 0
        # 0: left->right
        # 1: top->bottom
        # 2: right->left
        # 3: bottom->top
        
        direction = 0

        spiral = []
        while left_ptr <= right_ptr and top_ptr <= bottom_ptr:
            if direction == 0:
                for i in range(left_ptr, right_ptr+1):
                    spiral.append(matrix[top_ptr][i])
                top_ptr += 1
            if direction == 1:
                for i in range(top_ptr, bottom_ptr+1):
                    spiral.append(matrix[i][right_ptr])
                right_ptr -= 1
            if direction == 2:
                for i in range(right_ptr, left_ptr-1, -1):
                    spiral.append(matrix[bottom_ptr][i])
                bottom_ptr -= 1
            if direction == 3:
                for i in range(bottom_ptr, top_ptr-1, -1):
                    spiral.append(matrix[i][left_ptr])
                left_ptr += 1
                
            direction = (direction + 1) % 4
            



sol = Solution()
matrix = [[1,2,3],[4,5,6],[7,8,9]]
matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
sol.spiralOrder(matrix)