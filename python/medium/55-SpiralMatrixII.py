
class Solution:
    # def generateMatrix(self, n: int) -> List[List[int]]:
    def generateMatrix(self, n):

        """
            This solution is a modification of '54-SpiralMatrix.py', which is derived from this reference:
            https://www.youtube.com/watch?v=1ZGJzvkcLsA
        """        

        top_ptr = 0
        bottom_ptr = n-1
        left_ptr = 0
        right_ptr = n-1
        
        direction = 0
        # 0: left->right
        # 1: top->bottom
        # 2: right->left
        # 3: bottom->top
        
        ni = 1
        
        matrix = [[0]*n for _ in range(n)]
        # You CAN NOT use [[0]*n]*n here as the outer '*' operator will create n shallow copies of each [0]*n row
        # Thus, each row will point to the same address in memory...
        # Meaning that all rows in the matrix will be altered when just one is changed
        while left_ptr <= right_ptr and top_ptr <= bottom_ptr:
            if direction == 0:
                for i in range(left_ptr, right_ptr+1):
                    matrix[top_ptr][i] = ni
                    ni+=1
                top_ptr += 1
            if direction == 1:
                for i in range(top_ptr, bottom_ptr+1):
                    matrix[i][right_ptr] = ni
                    ni+=1
                right_ptr -= 1
            if direction == 2:
                for i in range(right_ptr, left_ptr-1, -1):
                    matrix[bottom_ptr][i] = ni
                    ni+=1
                bottom_ptr -= 1
            if direction == 3:
                for i in range(bottom_ptr, top_ptr-1, -1):
                    matrix[i][left_ptr] = ni
                    ni+=1
                left_ptr += 1
                
            direction = (direction + 1) % 4
            
        return matrix
            



sol = Solution()
print(sol.generateMatrix(3))