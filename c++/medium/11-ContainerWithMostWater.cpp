#include <vector>
#include <iostream>
#include <math.h>
using std::vector, std::cout, std::endl;


class Solution {
public:
    int maxArea(vector<int>& height) {

        /** 
            This algorithm uses a two-pointer approach to find the maximum area of water contained between two lines, represented by array elements
            The general criteria for a question to fit the two-pointer approach is:
            The problem involves finding two or more elements in a sorted or unsorted array that (when combined in some way) meets a certain condition
            Here, we attempt to find two heights in the array that, when used to calculate the area of a container, yield some maximum value
            
            Note that the 'certain condition' cannot be arbitrary
            For example, in TwoSum, the condition is that the sum of two numbers equals a target value - which is arbitrary
            Due to the arbitrary nature of the target value, the two-pointer approach is not applicable as, at each step, we do not know which pointer to move
            In ContainerWithMostWater, however, the condition is that the area of the container is maximized - this is not arbitrary
            Thus, at each step, we know that to maximize the area, we should always move the pointer pointing to the shorter height
            Now, if the TwoSum problem were modified such that we were working with a sorted array, then the two-pointer approach would be applicable since we would know which pointer to move based on whether the current sum was less than or greater than the target value
         */

        int left = 0;
        int right = height.size()-1;
        int maxArea = 0;
        int heightLeft;
        int heightRight;
        int min_h;
        int area;

        while (left != right){
            
            heightLeft = height[left];
            heightRight = height[right];
            
            min_h = std::min(heightLeft, heightRight);
            area = (right-left) * min_h;
            
            if (area > maxArea){
                maxArea = area;
            }
                        
            left = (heightLeft == min_h && heightLeft != heightRight) ? left + 1 : left;
            right = (heightRight == min_h) ? right - 1 : right;
            
        }

        return maxArea;
        
    }
};


int main(){

    Solution sol;
    vector<int> height;
    // height = {1,8,6,2,5,4,8,3,7};
    height = {1,1};
    cout << sol.maxArea(height) << endl;


    return 0;
}