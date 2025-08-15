#include <iostream>
#include <vector>
#include <cmath>

using std::string, std::cout, std::endl, std::vector;

class Solution {
public:
    int search(vector<int>& nums, int target) {

        /**
            Standard binary search algorithm
            Time Complexity: O(logn)
            Space Complexity: O(1)
         */

        int left = 0;
        int right = nums.size()-1;
        double mid;
        int num;

        while (left <= right){
        // This is critical. In binary search left=right is a valid condition that signifies the algorithm's last possible check (which is a completely valid, terminal state)
        // DO NOT exclude it by writing 'while (left != right)'
        // This final check is necessary when finding targets at the edge of the array: v = {1, 2, 3}, t=3

            mid = floor((left+right)/2);
            num = nums[mid];

            if (num == target){
                return mid;
            } else if (target < num){
                right = mid - 1;
            } else if (target > num){
                left = mid + 1;
            }
        };

        return -1;
    }
};


int main(){

    Solution sol;   

    // vector v{-1,0,3,5,9,12};
    // int t = 2;

    vector v{-5};
    int t = 5;
    cout << sol.search(v, t) << endl;

    return 0;
}