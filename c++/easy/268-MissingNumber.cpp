#include <iostream>
#include <vector>
using std::vector, std::cout, std::endl;

class Solution {
public:
    int missingNumber(vector<int>& nums) {

        /**
            This one's pretty easy and self-explanatory
            Time Complexity: O(n)
            Space Complexity: O(1)
        */

        int n = nums.size();
        int sum = 0;
        int trueSum = 0;
        int missingNum;

        for (int num:nums){
            sum += num;
        }

        for (int i=0; i<=n; i++){
            trueSum += i;
        }

        missingNum = trueSum - sum;
        return missingNum;
           
    }
};

int main(){


    Solution sol;

    vector<int> nums;
    nums = {9,6,4,2,3,5,7,0,1};

    cout << sol.missingNumber(nums) << endl;

    return 0;
}