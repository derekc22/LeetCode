#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::map;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        map<int, int> numMap;

        for (int i=0; i < nums.size(); i++){

            int curr = nums[i];
            int need = target - curr;

            if ( numMap.find(need) != numMap.end() ){
                vector<int>  sol = {i, numMap[need]};
                return sol;

            } else {
                numMap.insert({curr, i});
            }
        }

        return {};
        
    }
};

// In this solution, each number is visited. The number needed to reach the target calculated and then checked for in the hash map
// If the number is found, the indices of both the current number and the needed number are returned
// If the number is not found, the current number (key) and its index (value) are inserted into the hash map 
// The time complexity is O(n) - we only traverse the array once
// The space complexity is O(n) - we store the numbers in a hash map
// The access time for the hash map is O(1) on average

int main(){
    vector<int> arr = {3, 3};
    int target = 6;

    Solution solution;
    vector<int> sol = solution.twoSum(arr, target);
    
    for (int elem : sol){
        std::cout << elem << " ";
    }
}